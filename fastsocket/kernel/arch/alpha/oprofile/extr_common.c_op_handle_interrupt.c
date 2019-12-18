#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pt_regs {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* reset_ctr ) (TYPE_1__*,unsigned long) ;int /*<<< orphan*/  (* handle_interrupt ) (unsigned long,struct pt_regs*,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {unsigned long need_reset; } ;

/* Variables and functions */
 int /*<<< orphan*/  ctr ; 
 TYPE_3__* model ; 
 TYPE_1__ reg ; 
 int /*<<< orphan*/  stub1 (unsigned long,struct pt_regs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,unsigned long) ; 

__attribute__((used)) static void
op_handle_interrupt(unsigned long which, struct pt_regs *regs)
{
	model->handle_interrupt(which, regs, ctr);

	/* If the user has selected an interrupt frequency that is
	   not exactly the width of the counter, write a new value
	   into the counter such that it'll overflow after N more
	   events.  */
	if ((reg.need_reset >> which) & 1)
		model->reset_ctr(&reg, which);
}