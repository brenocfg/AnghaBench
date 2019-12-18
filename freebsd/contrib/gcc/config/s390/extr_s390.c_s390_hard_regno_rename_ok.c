#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* machine; } ;
struct TYPE_3__ {scalar_t__ base_reg; } ;

/* Variables and functions */
 unsigned int REGNO (scalar_t__) ; 
 TYPE_2__* cfun ; 

bool
s390_hard_regno_rename_ok (unsigned int old_reg, unsigned int new_reg)
{
   /* Once we've decided upon a register to use as base register, it must
      no longer be used for any other purpose.  */
  if (cfun->machine->base_reg)
    if (REGNO (cfun->machine->base_reg) == old_reg
	|| REGNO (cfun->machine->base_reg) == new_reg)
      return false;

  return true;
}