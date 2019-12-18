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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct wb35_reg_queue {int INDEX; struct wb35_reg_queue* Next; struct urb* urb; struct usb_ctrlrequest* pUsbReq; int /*<<< orphan*/ * pBuffer; scalar_t__ DIRECT; } ;
struct wb35_reg {int /*<<< orphan*/  EP0VM_spin_lock; struct wb35_reg_queue* reg_last; struct wb35_reg_queue* reg_first; } ;
struct usb_ctrlrequest {int bRequestType; int bRequest; void* wLength; void* wIndex; void* wValue; } ;
struct urb {int dummy; } ;
struct hw_data {scalar_t__ SurpriseRemove; struct wb35_reg reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int USB_DIR_IN ; 
 int USB_RECIP_DEVICE ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  Wb35Reg_EP0VM_start (struct hw_data*) ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  kfree (struct wb35_reg_queue*) ; 
 struct wb35_reg_queue* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 struct urb* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 

unsigned char
Wb35Reg_Read(struct hw_data * pHwData, u16 RegisterNo,  u32 * pRegisterValue )
{
	struct wb35_reg *reg = &pHwData->reg;
	struct usb_ctrlrequest * dr;
	struct urb	*urb;
	struct wb35_reg_queue *reg_queue;
	u16		UrbSize;

	// Module shutdown
	if (pHwData->SurpriseRemove)
		return false;

	// update the variable by send Urb to read register ------------------------------------
	UrbSize = sizeof(struct wb35_reg_queue) + sizeof(struct usb_ctrlrequest);
	reg_queue = kzalloc(UrbSize, GFP_ATOMIC);
	urb = usb_alloc_urb(0, GFP_ATOMIC);
	if( urb && reg_queue )
	{
		reg_queue->DIRECT = 0;// read register
		reg_queue->INDEX = RegisterNo;
		reg_queue->pBuffer = pRegisterValue;
		dr = (struct usb_ctrlrequest *)((u8 *)reg_queue + sizeof(struct wb35_reg_queue));
		dr->bRequestType = USB_TYPE_VENDOR|USB_RECIP_DEVICE|USB_DIR_IN;
		dr->bRequest = 0x01; // USB or vendor-defined request code, burst mode
		dr->wValue = cpu_to_le16(0x0);
		dr->wIndex = cpu_to_le16 (RegisterNo);
		dr->wLength = cpu_to_le16 (4);

		// Enter the sending queue
		reg_queue->Next = NULL;
		reg_queue->pUsbReq = dr;
		reg_queue->urb = urb;
		spin_lock_irq ( &reg->EP0VM_spin_lock );
		if( reg->reg_first == NULL )
			reg->reg_first = reg_queue;
		else
			reg->reg_last->Next = reg_queue;
		reg->reg_last = reg_queue;

		spin_unlock_irq( &reg->EP0VM_spin_lock );

		// Start EP0VM
		Wb35Reg_EP0VM_start( pHwData );

		return true;
	} else {
		if (urb)
			usb_free_urb( urb );
		kfree(reg_queue);
		return false;
	}
}