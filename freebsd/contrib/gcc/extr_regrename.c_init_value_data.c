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
struct value_data {scalar_t__ max_value_regs; TYPE_1__* e; } ;
struct TYPE_2__ {int oldest_regno; int /*<<< orphan*/  next_regno; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int FIRST_PSEUDO_REGISTER ; 
 int /*<<< orphan*/  INVALID_REGNUM ; 
 int /*<<< orphan*/  VOIDmode ; 

__attribute__((used)) static void
init_value_data (struct value_data *vd)
{
  int i;
  for (i = 0; i < FIRST_PSEUDO_REGISTER; ++i)
    {
      vd->e[i].mode = VOIDmode;
      vd->e[i].oldest_regno = i;
      vd->e[i].next_regno = INVALID_REGNUM;
    }
  vd->max_value_regs = 0;
}