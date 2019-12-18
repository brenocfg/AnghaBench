#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pt_regs {int dummy; } ;
struct TYPE_4__ {int cpic_civr; int cpic_cimr; int cpic_cisr; } ;
struct TYPE_5__ {TYPE_1__ im_cpic; } ;
typedef  TYPE_2__ immap_t ;
struct TYPE_6__ {int /*<<< orphan*/  dev_id; int /*<<< orphan*/  (* handler ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ IMAP_ADDR ; 
 TYPE_3__* cpm_vecs ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int vec ; 

__attribute__((used)) static	void
cpm_interrupt(int irq, void * dev, struct pt_regs * regs)
{
	/* uint	vec; */

	/* mles: Note that this stuff is currently being performed by
	 * M68360_do_irq(int vec, struct pt_regs *fp), in ../ints.c  */

	/* figure out the vector */
	/* call that vector's handler */
	/* clear the irq's bit in the service register */

#if 0 /* old 860 stuff: */
	/* Get the vector by setting the ACK bit and then reading
	 * the register.
	 */
	((volatile immap_t *)IMAP_ADDR)->im_cpic.cpic_civr = 1;
	vec = ((volatile immap_t *)IMAP_ADDR)->im_cpic.cpic_civr;
	vec >>= 11;


	if (cpm_vecs[vec].handler != 0)
		(*cpm_vecs[vec].handler)(cpm_vecs[vec].dev_id);
	else
		((immap_t *)IMAP_ADDR)->im_cpic.cpic_cimr &= ~(1 << vec);

	/* After servicing the interrupt, we have to remove the status
	 * indicator.
	 */
	((immap_t *)IMAP_ADDR)->im_cpic.cpic_cisr |= (1 << vec);
#endif
	
}