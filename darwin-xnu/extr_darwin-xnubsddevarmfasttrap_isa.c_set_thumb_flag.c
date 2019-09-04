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
typedef  int user_addr_t ;
struct TYPE_3__ {int /*<<< orphan*/  cpsr; } ;
typedef  TYPE_1__ arm_saved_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  PSR_TF ; 

__attribute__((used)) static void set_thumb_flag(arm_saved_state_t *regs, user_addr_t pc)
{
	if (pc & 1) {
		regs->cpsr |= PSR_TF;
	} else {
		regs->cpsr &= ~PSR_TF;
	}
}