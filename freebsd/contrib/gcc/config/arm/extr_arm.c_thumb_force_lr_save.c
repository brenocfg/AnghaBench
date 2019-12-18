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
struct TYPE_3__ {int /*<<< orphan*/  lr_save_eliminated; } ;

/* Variables and functions */
 size_t LR_REGNUM ; 
 TYPE_2__* cfun ; 
 int /*<<< orphan*/  leaf_function_p () ; 
 scalar_t__* regs_ever_live ; 
 scalar_t__ thumb_far_jump_used_p () ; 

__attribute__((used)) static bool
thumb_force_lr_save (void)
{
  return !cfun->machine->lr_save_eliminated
	 && (!leaf_function_p ()
	     || thumb_far_jump_used_p ()
	     || regs_ever_live [LR_REGNUM]);
}