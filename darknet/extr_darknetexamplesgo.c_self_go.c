#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  network ;
struct TYPE_3__ {int row; int col; } ;
typedef  TYPE_1__ move ;
typedef  int /*<<< orphan*/  mcts_tree ;

/* Variables and functions */
 int /*<<< orphan*/  board_to_string (char*,float*) ; 
 void* calloc (int,int) ; 
 int /*<<< orphan*/  copy_cpu (int,float*,int,float*,int) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flip_board (float*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,float,float) ; 
 int /*<<< orphan*/ * load_network (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_weights (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  memset (float*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  move_go (float*,int,int,int) ; 
 int /*<<< orphan*/ * move_mcts (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * parse_network_cfg (char*) ; 
 TYPE_1__ pick_move (int /*<<< orphan*/ *,float,int) ; 
 int /*<<< orphan*/ * run_mcts (int /*<<< orphan*/ *,int /*<<< orphan*/ *,float*,float*,int,int,float,int /*<<< orphan*/ ) ; 
 float score_game (float*) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  srand (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ ) ; 

void self_go(char *filename, char *weightfile, char *f2, char *w2, int multi)
{
    mcts_tree *tree1 = 0;
    mcts_tree *tree2 = 0;
    network *net = load_network(filename, weightfile, 0);
    //set_batch_network(net, 1);

    network *net2;
    if (f2) {
        net2 = parse_network_cfg(f2);
        if(w2){
            load_weights(net2, w2);
        }
    } else {
        net2 = calloc(1, sizeof(network));
        *net2 = *net;
    }
    srand(time(0));
    char boards[600][93];
    int count = 0;
    //set_batch_network(net, 1);
    //set_batch_network(net2, 1);
    float *board = calloc(19*19*3, sizeof(float));
    flip_board(board);
    float *one = calloc(19*19*3, sizeof(float));
    float *two = calloc(19*19*3, sizeof(float));
    int done = 0;
    int player = 1;
    int p1 = 0;
    int p2 = 0;
    int total = 0;
    float temp = .1;
    int mcts_iters = 500;
    float cpuct = 5;
    while(1){
        if (done){
            tree1 = move_mcts(tree1, -1);
            tree2 = move_mcts(tree2, -1);
            float score = score_game(board);
            if((score > 0) == (total%2==0)) ++p1;
            else ++p2;
            ++total;
            fprintf(stderr, "Total: %d, Player 1: %f, Player 2: %f\n", total, (float)p1/total, (float)p2/total);
            sleep(1);
            /*
               int i = (score > 0)? 0 : 1;
               int j;
               for(; i < count; i += 2){
               for(j = 0; j < 93; ++j){
               printf("%c", boards[i][j]);
               }
               printf("\n");
               }
             */
            memset(board, 0, 3*19*19*sizeof(float));
            flip_board(board);
            player = 1;
            done = 0;
            count = 0;
            fflush(stdout);
            fflush(stderr);
        }
        //print_board(stderr, board, 1, 0);
        //sleep(1);

        if ((total%2==0) == (player==1)){
            //mcts_iters = 4500;   
            cpuct = 5;
        } else {
            //mcts_iters = 500;
            cpuct = 1;
        }
        network *use = ((total%2==0) == (player==1)) ? net : net2;
        mcts_tree *t = ((total%2==0) == (player==1)) ? tree1 : tree2;
        t = run_mcts(t, use, board, two, player, mcts_iters, cpuct, 0);
        move m = pick_move(t, temp, player);
        if(((total%2==0) == (player==1))) tree1 = t;
        else tree2 = t;

        tree1 = move_mcts(tree1, m.row*19 + m.col);
        tree2 = move_mcts(tree2, m.row*19 + m.col);

        if(m.row == 19){
            done = 1;
            continue;
        }
        int row = m.row;
        int col = m.col;

        float *swap = two;
        two = one;
        one = swap;

        if(player < 0) flip_board(board);
        boards[count][0] = row;
        boards[count][1] = col;
        board_to_string(boards[count] + 2, board);
        if(player < 0) flip_board(board);
        ++count;

        move_go(board, player, row, col);
        copy_cpu(19*19*3, board, 1, one, 1);

        player = -player;
    }
}