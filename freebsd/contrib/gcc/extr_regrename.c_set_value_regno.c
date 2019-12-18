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
struct value_data {unsigned int max_value_regs; TYPE_1__* e; } ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
struct TYPE_2__ {int mode; } ;

/* Variables and functions */
 unsigned int** hard_regno_nregs ; 

__attribute__((used)) static void
set_value_regno (unsigned int regno, enum machine_mode mode,
		 struct value_data *vd)
{
  unsigned int nregs;

  vd->e[regno].mode = mode;

  nregs = hard_regno_nregs[regno][mode];
  if (nregs > vd->max_value_regs)
    vd->max_value_regs = nregs;
}