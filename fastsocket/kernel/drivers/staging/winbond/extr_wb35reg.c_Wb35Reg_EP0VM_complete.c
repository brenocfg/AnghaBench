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
struct wb35_reg_queue {struct wb35_reg_queue* Next; } ;
struct wb35_reg {void* EP0vm_state; scalar_t__ EP0VM_status; int /*<<< orphan*/  EP0VM_spin_lock; struct wb35_reg_queue* reg_first; struct wb35_reg_queue* reg_last; int /*<<< orphan*/  RegFireCount; } ;
struct urb {scalar_t__ status; scalar_t__ context; } ;
struct hw_data {int SurpriseRemove; struct wb35_reg reg; } ;

/* Variables and functions */
 void* VM_COMPLETED ; 
 void* VM_STOP ; 
 int /*<<< orphan*/  Wb35Reg_EP0VM (struct hw_data*) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct wb35_reg_queue*) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 

void
Wb35Reg_EP0VM_complete(struct urb *urb)
{
	struct hw_data *  pHwData = (struct hw_data *)urb->context;
	struct wb35_reg *reg = &pHwData->reg;
	struct wb35_reg_queue *reg_queue;


	// Variable setting
	reg->EP0vm_state = VM_COMPLETED;
	reg->EP0VM_status = urb->status;

	if (pHwData->SurpriseRemove) { // Let WbWlanHalt to handle surprise remove
		reg->EP0vm_state = VM_STOP;
		atomic_dec(&reg->RegFireCount);
	} else {
		// Complete to send, remove the URB from the first
		spin_lock_irq( &reg->EP0VM_spin_lock );
		reg_queue = reg->reg_first;
		if (reg_queue == reg->reg_last)
			reg->reg_last = NULL;
		reg->reg_first = reg->reg_first->Next;
		spin_unlock_irq( &reg->EP0VM_spin_lock );

		if (reg->EP0VM_status) {
#ifdef _PE_REG_DUMP_
			printk("EP0 IoCompleteRoutine return error\n");
#endif
			reg->EP0vm_state = VM_STOP;
			pHwData->SurpriseRemove = 1;
		} else {
			// Success. Update the result

			// Start the next send
			Wb35Reg_EP0VM(pHwData);
		}

   		kfree(reg_queue);
	}

	usb_free_urb(urb);
}