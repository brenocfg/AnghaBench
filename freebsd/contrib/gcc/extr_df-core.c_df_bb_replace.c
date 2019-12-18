#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct df {int num_problems_defined; struct dataflow** problems_in_order; } ;
struct dataflow {scalar_t__ block_info; } ;
typedef  TYPE_1__* basic_block ;
struct TYPE_4__ {int index; } ;

/* Variables and functions */
 int /*<<< orphan*/  SET_BASIC_BLOCK (int,TYPE_1__*) ; 
 void* df_get_bb_info (struct dataflow*,int) ; 
 int /*<<< orphan*/  df_grow_bb_info (struct dataflow*) ; 
 int /*<<< orphan*/  df_set_bb_info (struct dataflow*,int,void*) ; 

void 
df_bb_replace (struct df *df, int old_index, basic_block new_block)
{
  int p;

  for (p = 0; p < df->num_problems_defined; p++)
    {
      struct dataflow *dflow = df->problems_in_order[p];
      if (dflow->block_info)
	{
	  void *temp;

	  df_grow_bb_info (dflow);

	  /* The old switcheroo.  */

	  temp = df_get_bb_info (dflow, old_index);
	  df_set_bb_info (dflow, old_index, 
			  df_get_bb_info (dflow, new_block->index));
	  df_set_bb_info (dflow, new_block->index, temp);
	}
    }

  SET_BASIC_BLOCK (old_index, new_block);
  new_block->index = old_index;
}