#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct wb35_reg_queue {struct urb* urb; struct wb35_reg_queue* Next; } ;
struct wb35_reg {scalar_t__ EP0vm_state; int /*<<< orphan*/  EP0VM_spin_lock; struct wb35_reg_queue* reg_first; struct wb35_reg_queue* reg_last; } ;
struct urb {int dummy; } ;
struct hw_data {struct wb35_reg reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  Uxx_power_off_procedure (struct hw_data*) ; 
 scalar_t__ VM_STOP ; 
 int /*<<< orphan*/  kfree (struct wb35_reg_queue*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 

void
Wb35Reg_destroy(struct hw_data * pHwData)
{
	struct wb35_reg *reg = &pHwData->reg;
	struct urb	*urb;
	struct wb35_reg_queue *reg_queue;


	Uxx_power_off_procedure(pHwData);

	// Wait for Reg operation completed
	do {
		msleep(10); // Delay for waiting function enter 940623.1.a
	} while (reg->EP0vm_state != VM_STOP);
	msleep(10);  // Delay for waiting function enter 940623.1.b

	// Release all the data in RegQueue
	spin_lock_irq( &reg->EP0VM_spin_lock );
	reg_queue = reg->reg_first;
	while (reg_queue) {
		if (reg_queue == reg->reg_last)
			reg->reg_last = NULL;
		reg->reg_first = reg->reg_first->Next;

		urb = reg_queue->urb;
		spin_unlock_irq( &reg->EP0VM_spin_lock );
		if (urb) {
			usb_free_urb(urb);
			kfree(reg_queue);
		} else {
			#ifdef _PE_REG_DUMP_
			printk("EP0 queue release error\n");
			#endif
		}
		spin_lock_irq( &reg->EP0VM_spin_lock );

		reg_queue = reg->reg_first;
	}
	spin_unlock_irq( &reg->EP0VM_spin_lock );
}