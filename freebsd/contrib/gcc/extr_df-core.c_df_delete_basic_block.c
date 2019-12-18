#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct df {int num_problems_defined; struct dataflow** problems_in_order; } ;
struct dataflow {TYPE_1__* problem; } ;
typedef  int /*<<< orphan*/  basic_block ;
struct TYPE_2__ {int /*<<< orphan*/  (* free_bb_fun ) (struct dataflow*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BASIC_BLOCK (int) ; 
 int /*<<< orphan*/  df_get_bb_info (struct dataflow*,int) ; 
 int /*<<< orphan*/  stub1 (struct dataflow*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
df_delete_basic_block (struct df *df, int bb_index)
{
  basic_block bb = BASIC_BLOCK (bb_index);
  int i;
  
  for (i = 0; i < df->num_problems_defined; i++)
    {
      struct dataflow *dflow = df->problems_in_order[i];
      if (dflow->problem->free_bb_fun)
	dflow->problem->free_bb_fun 
	  (dflow, bb, df_get_bb_info (dflow, bb_index)); 
    }
}