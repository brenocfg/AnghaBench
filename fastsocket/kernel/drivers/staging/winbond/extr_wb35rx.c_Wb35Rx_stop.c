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
struct wb35_rx {scalar_t__ EP3vm_state; int /*<<< orphan*/  RxUrb; } ;
struct hw_data {struct wb35_rx Wb35Rx; } ;

/* Variables and functions */
 scalar_t__ VM_RUNNING ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  usb_unlink_urb (int /*<<< orphan*/ ) ; 

void Wb35Rx_stop(struct hw_data * pHwData)
{
	struct wb35_rx *pWb35Rx = &pHwData->Wb35Rx;

	// Canceling the Irp if already sends it out.
	if (pWb35Rx->EP3vm_state == VM_RUNNING) {
		usb_unlink_urb( pWb35Rx->RxUrb ); // Only use unlink, let Wb35Rx_destroy to free them
		#ifdef _PE_RX_DUMP_
		printk("EP3 Rx stop\n");
		#endif
	}
}