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
struct TYPE_2__ {void** rec_ctrl; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 void* IO_STATE (void**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * R_IRQ_MASK1_SET ; 
 void** R_SERIAL0_REC_CTRL ; 
 void** R_VECT_MASK_SET ; 
 int /*<<< orphan*/  enable ; 
 TYPE_1__* kgdb_port ; 
 int /*<<< orphan*/  rec_enable ; 
 int /*<<< orphan*/  serial ; 
 int /*<<< orphan*/  set ; 

void
enableDebugIRQ(void)
{
	if (!kgdb_port)
		return;

	*R_IRQ_MASK1_SET = kgdb_port->irq;
	/* use R_VECT_MASK directly, since we really bypass Linux normal
	 * IRQ handling in kgdb anyway, we don't need to use enable_irq
	 */
	*R_VECT_MASK_SET = IO_STATE(R_VECT_MASK_SET, serial, set);

	*kgdb_port->rec_ctrl = IO_STATE(R_SERIAL0_REC_CTRL, rec_enable, enable);
}