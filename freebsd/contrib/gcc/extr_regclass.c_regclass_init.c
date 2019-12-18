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
struct TYPE_2__ {int mem_cost; int* cost; } ;

/* Variables and functions */
 int N_REG_CLASSES ; 
 TYPE_1__ init_cost ; 
 int no_global_reg_vars ; 
 int /*<<< orphan*/ * reg_pref ; 

void
regclass_init (void)
{
  int i;

  init_cost.mem_cost = 10000;
  for (i = 0; i < N_REG_CLASSES; i++)
    init_cost.cost[i] = 10000;

  /* This prevents dump_flow_info from losing if called
     before regclass is run.  */
  reg_pref = NULL;

  /* No more global register variables may be declared.  */
  no_global_reg_vars = 1;
}