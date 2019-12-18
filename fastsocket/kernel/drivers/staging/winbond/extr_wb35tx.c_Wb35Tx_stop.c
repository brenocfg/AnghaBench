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
struct wb35_tx {scalar_t__ EP2vm_state; scalar_t__ EP4vm_state; int /*<<< orphan*/  Tx4Urb; int /*<<< orphan*/  Tx2Urb; } ;
struct hw_data {struct wb35_tx Wb35Tx; } ;

/* Variables and functions */
 scalar_t__ VM_RUNNING ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  usb_unlink_urb (int /*<<< orphan*/ ) ; 

void Wb35Tx_stop(struct hw_data * pHwData)
{
	struct wb35_tx *pWb35Tx = &pHwData->Wb35Tx;

	// Trying to canceling the Trp of EP2
	if (pWb35Tx->EP2vm_state == VM_RUNNING)
		usb_unlink_urb( pWb35Tx->Tx2Urb ); // Only use unlink, let Wb35Tx_destrot to free them
	#ifdef _PE_TX_DUMP_
	printk("EP2 Tx stop\n");
	#endif

	// Trying to canceling the Irp of EP4
	if (pWb35Tx->EP4vm_state == VM_RUNNING)
		usb_unlink_urb( pWb35Tx->Tx4Urb ); // Only use unlink, let Wb35Tx_destrot to free them
	#ifdef _PE_TX_DUMP_
	printk("EP4 Tx stop\n");
	#endif
}