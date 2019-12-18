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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct wb35_reg_queue {int DIRECT; int /*<<< orphan*/  VALUE; int /*<<< orphan*/ * pBuffer; struct urb* urb; struct usb_ctrlrequest* pUsbReq; } ;
struct wb35_reg {int /*<<< orphan*/  RegFireCount; int /*<<< orphan*/  EP0vm_state; int /*<<< orphan*/  EP0VM_spin_lock; struct wb35_reg_queue* reg_first; scalar_t__ SyncIoPause; } ;
struct usb_ctrlrequest {int /*<<< orphan*/  wLength; } ;
struct urb {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  udev; } ;
struct hw_data {TYPE_1__ WbUsb; scalar_t__ SurpriseRemove; struct wb35_reg reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  REG_DIRECTION (int /*<<< orphan*/ ,struct wb35_reg_queue*) ; 
 int /*<<< orphan*/  VM_RUNNING ; 
 int /*<<< orphan*/  VM_STOP ; 
 int /*<<< orphan*/  Wb35Reg_EP0VM_complete ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_fill_control_urb (struct urb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 

void
Wb35Reg_EP0VM(struct hw_data * pHwData )
{
	struct wb35_reg *reg = &pHwData->reg;
	struct urb	*urb;
	struct usb_ctrlrequest *dr;
	u32 *		pBuffer;
	int			ret = -1;
	struct wb35_reg_queue *reg_queue;


	if (reg->SyncIoPause)
		goto cleanup;

	if (pHwData->SurpriseRemove)
		goto cleanup;

	// Get the register data and send to USB through Irp
	spin_lock_irq( &reg->EP0VM_spin_lock );
	reg_queue = reg->reg_first;
	spin_unlock_irq( &reg->EP0VM_spin_lock );

	if (!reg_queue)
		goto cleanup;

	// Get an Urb, send it
	urb = (struct urb *)reg_queue->urb;

	dr = reg_queue->pUsbReq;
	urb = reg_queue->urb;
	pBuffer = reg_queue->pBuffer;
	if (reg_queue->DIRECT == 1) // output
		pBuffer = &reg_queue->VALUE;

	usb_fill_control_urb( urb, pHwData->WbUsb.udev,
			      REG_DIRECTION(pHwData->WbUsb.udev,reg_queue),
			      (u8 *)dr,pBuffer,cpu_to_le16(dr->wLength),
			      Wb35Reg_EP0VM_complete, (void*)pHwData);

	reg->EP0vm_state = VM_RUNNING;

	ret = usb_submit_urb(urb, GFP_ATOMIC);

	if (ret < 0) {
#ifdef _PE_REG_DUMP_
		printk("EP0 Irp sending error\n");
#endif
		goto cleanup;
	}

	return;

 cleanup:
	reg->EP0vm_state = VM_STOP;
	atomic_dec(&reg->RegFireCount);
}