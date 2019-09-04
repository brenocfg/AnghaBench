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
struct TYPE_6__ {int total_count; } ;
typedef  TYPE_1__ mcts_tree ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 TYPE_1__* run_mcts (TYPE_1__*,int /*<<< orphan*/ *,float*,float*,int,int,float,double) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdin_ready () ; 
 double what_time_is_it_now () ; 

mcts_tree *ponder(mcts_tree *tree, network *net, float *b, float *ko, int player, float cpuct)
{
    double t = what_time_is_it_now();
    int count = 0;
    if (tree) count = tree->total_count;
    while(!stdin_ready()){
        if (what_time_is_it_now() - t > 120) break;
        tree = run_mcts(tree, net, b, ko, player, 100000, cpuct, .1);
    }
    fprintf(stderr, "Pondered %d moves...\n", tree->total_count - count);
    return tree;
}