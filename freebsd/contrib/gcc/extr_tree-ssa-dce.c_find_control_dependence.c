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
struct edge_list {int dummy; } ;
typedef  TYPE_1__* edge ;
typedef  scalar_t__ basic_block ;
struct TYPE_3__ {int flags; } ;

/* Variables and functions */
 int EDGE_ABNORMAL ; 
 scalar_t__ ENTRY_BLOCK_PTR ; 
 scalar_t__ EXIT_BLOCK_PTR ; 
 TYPE_1__* INDEX_EDGE (struct edge_list*,int) ; 
 scalar_t__ INDEX_EDGE_PRED_BB (struct edge_list*,int) ; 
 scalar_t__ INDEX_EDGE_SUCC_BB (struct edge_list*,int) ; 
 scalar_t__ find_pdom (scalar_t__) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  set_control_dependence_map_bit (scalar_t__,int) ; 
 scalar_t__ single_succ (scalar_t__) ; 

__attribute__((used)) static void
find_control_dependence (struct edge_list *el, int edge_index)
{
  basic_block current_block;
  basic_block ending_block;

  gcc_assert (INDEX_EDGE_PRED_BB (el, edge_index) != EXIT_BLOCK_PTR);

  if (INDEX_EDGE_PRED_BB (el, edge_index) == ENTRY_BLOCK_PTR)
    ending_block = single_succ (ENTRY_BLOCK_PTR);
  else
    ending_block = find_pdom (INDEX_EDGE_PRED_BB (el, edge_index));

  for (current_block = INDEX_EDGE_SUCC_BB (el, edge_index);
       current_block != ending_block && current_block != EXIT_BLOCK_PTR;
       current_block = find_pdom (current_block))
    {
      edge e = INDEX_EDGE (el, edge_index);

      /* For abnormal edges, we don't make current_block control
	 dependent because instructions that throw are always necessary
	 anyway.  */
      if (e->flags & EDGE_ABNORMAL)
	continue;

      set_control_dependence_map_bit (current_block, edge_index);
    }
}