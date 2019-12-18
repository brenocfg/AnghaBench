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
typedef  TYPE_1__* depth_first_search_ds ;
struct TYPE_3__ {int /*<<< orphan*/  visited_blocks; scalar_t__ sp; int /*<<< orphan*/  stack; } ;

/* Variables and functions */
 int /*<<< orphan*/  XNEWVEC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  basic_block ; 
 int /*<<< orphan*/  last_basic_block ; 
 int /*<<< orphan*/  n_basic_blocks ; 
 int /*<<< orphan*/  sbitmap_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbitmap_zero (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
flow_dfs_compute_reverse_init (depth_first_search_ds data)
{
  /* Allocate stack for back-tracking up CFG.  */
  data->stack = XNEWVEC (basic_block, n_basic_blocks);
  data->sp = 0;

  /* Allocate bitmap to track nodes that have been visited.  */
  data->visited_blocks = sbitmap_alloc (last_basic_block);

  /* None of the nodes in the CFG have been visited yet.  */
  sbitmap_zero (data->visited_blocks);

  return;
}