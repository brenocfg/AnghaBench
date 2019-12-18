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
typedef  size_t u32 ;
struct wb35_rx {int* RxOwner; scalar_t__ rx_halt; int /*<<< orphan*/  EP3vm_state; scalar_t__ RxBufferId; scalar_t__ RxProcessIndex; scalar_t__ ByteReceived; } ;
struct hw_data {struct wb35_rx Wb35Rx; } ;

/* Variables and functions */
 size_t MAX_USB_RX_BUFFER_NUMBER ; 
 int /*<<< orphan*/  VM_STOP ; 

__attribute__((used)) static void Wb35Rx_reset_descriptor(  struct hw_data * pHwData )
{
	struct wb35_rx *pWb35Rx = &pHwData->Wb35Rx;
	u32	i;

	pWb35Rx->ByteReceived = 0;
	pWb35Rx->RxProcessIndex = 0;
	pWb35Rx->RxBufferId = 0;
	pWb35Rx->EP3vm_state = VM_STOP;
	pWb35Rx->rx_halt = 0;

	// Initial the Queue. The last buffer is reserved for used if the Rx resource is unavailable.
	for( i=0; i<MAX_USB_RX_BUFFER_NUMBER; i++ )
		pWb35Rx->RxOwner[i] = 1;
}