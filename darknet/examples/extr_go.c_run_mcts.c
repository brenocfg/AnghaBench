#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  network ;
struct TYPE_6__ {int* visit_count; int /*<<< orphan*/  board; } ;
typedef  TYPE_1__ mcts_tree ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compare_board (int /*<<< orphan*/ ,float*) ; 
 int /*<<< orphan*/  copy_board (float*) ; 
 TYPE_1__* expand (int /*<<< orphan*/ ,float*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flip_board (float*) ; 
 int max_int_index (int*,int) ; 
 int /*<<< orphan*/  select_mcts (TYPE_1__*,int /*<<< orphan*/ *,float*,float) ; 
 double what_time_is_it_now () ; 

mcts_tree *run_mcts(mcts_tree *tree, network *net, float *board, float *ko, int player, int n, float cpuct, float secs)
{
    int i;
    double t = what_time_is_it_now();
    if(player < 0) flip_board(board);
    if(!tree) tree = expand(copy_board(board), ko, net);
    assert(compare_board(tree->board, board));
    for(i = 0; i < n; ++i){
        if (secs > 0 && (what_time_is_it_now() - t) > secs) break;
        int max_i = max_int_index(tree->visit_count, 19*19+1);
        if (tree->visit_count[max_i] >= n) break;
        select_mcts(tree, net, ko, cpuct);
    }
    if(player < 0) flip_board(board);
    //fprintf(stderr, "%f Seconds\n", what_time_is_it_now() - t);
    return tree;
}