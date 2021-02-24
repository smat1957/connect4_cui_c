#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>
//盤面の広さ設定
#define BOARD_SQUARE 10
//盤面の出力
void Board_Output(void);
//入力処理
void Game(void);
//盤面の調査
void Board_Scan(int x, int y);
//置いた場所を中心に並ぶ個数の調査
int Board_Scan_Sub( int x, int y, int move_x, int move_y );
//ゲーム終了処理
void Finish(void);
int board[BOARD_SQUARE][BOARD_SQUARE] = {{0}};
int player_number = 1;

int main(void){
    int i;
    Board_Output();
    printf("ゲームスタート！\n");
    for( i = 0; i < (BOARD_SQUARE * BOARD_SQUARE); i++ ){
        Game();
        Board_Output();
        if( player_number < 2 ) player_number++;
        else player_number = 1;
    }
    return 0;
}

//盤面の出力－－－－－－－－－－－－－－－－－－－－－－－－－－－－
void Board_Output(void){
    int i, j;
    printf("  ");
    for( i = 0; i < BOARD_SQUARE; i++ ){
        printf("%2d",i);
    }
    puts("");
    for( i = 0; i < BOARD_SQUARE; i++ ){
        printf("%2d ",i);
        for( j = 0; j < BOARD_SQUARE; j++ ){
            switch( board[j][i] ){
                case 0:     printf("・"); break;
                case 1:     printf("〇"); break;
                case 2:     printf("⚫"); break;
            }
        }
        puts("");
    }
    puts("");
}

//決着～ゲーム終了－－－－－－－－－－－－－－－－－－－－－－－－－－－－－
void Finish(void){
    Board_Output();
    printf("%dP（",player_number);
    switch( player_number ){
        case 0:     printf("・"); break;
        case 1:     printf("○"); break;
        case 2:     printf("●"); break;
    }
    printf("）の勝利です！\n");

    exit(0);
}

//入力処理－－－－－－－－－－－－－－－－－－－－－－－－－－－－－
void Game(void){
    int x, y;
    printf("%dP（",player_number);
    switch( player_number ){
        case 0:     printf("・"); break;
        case 1:     printf("○"); break;
        case 2:     printf("●"); break;
    }
    printf("）のターンです。\n");
    while(1){
        while(1){
            printf("置く場所を決めてください(x y) "); scanf("%d %d",&x ,&y);
            if( x >= 0 && x < BOARD_SQUARE && y >= 0 && y < BOARD_SQUARE ) break;
            else printf("その場所には置けません\n");
        }
        if( board[x][y] == 0 ){
            board[x][y] = player_number;
            break;
        } else printf("その場所には置けません\n");
    }
    Board_Scan(x, y);
}

//盤面の調査（5個並んだかの調査）－－－－－－－－－－－－－－－－－－－－－－－－－－
void Board_Scan( int x, int y ){
    int n[4];                  //8方向（直線4本分）に並んだ数
    int move_x, move_y;
    int i;
    move_x = 1; move_y = 1;     //[＼]方向
    n[0] = Board_Scan_Sub( x, y, move_x, move_y );
    move_x = 0; move_y = 1;     //[│]方向
    n[1] = Board_Scan_Sub( x, y, move_x, move_y );
    move_x = 1; move_y = 0;     //[─]方向
    n[2] = Board_Scan_Sub( x, y, move_x, move_y );
    move_x = -1; move_y = 1;    //[／]方向
    n[3] = Board_Scan_Sub( x, y, move_x, move_y );
    for( i = 0; i < 4; i++ ){
        if(n[i] == 5) Finish();
    }
}

int Board_Scan_Sub( int x, int y, int move_x, int move_y ){
    int n = 1;                                 //置いた場所の1個分で初期化
    int i;
    for( i = 1; i < 5; i++ ){
        if( board[ x+(move_x*i) ][ y+(move_y*i) ]==player_number ) n += 1;
        else break;
    }
    for( i = 1; i < 5; i++ ){
        if( board[ x+(-1*move_x*i) ][ y+(-1*move_y*i) ]==player_number ) n += 1;
        else break;
    }
    return n;
}
