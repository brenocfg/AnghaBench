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
struct wb35_tx {void* Tx4Urb; void* Tx2Urb; } ;
struct hw_data {struct wb35_tx Wb35Tx; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 void* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (void*) ; 

unsigned char Wb35Tx_initial(struct hw_data * pHwData)
{
	struct wb35_tx *pWb35Tx = &pHwData->Wb35Tx;

	pWb35Tx->Tx4Urb = usb_alloc_urb(0, GFP_ATOMIC);
	if (!pWb35Tx->Tx4Urb)
		return false;

	pWb35Tx->Tx2Urb = usb_alloc_urb(0, GFP_ATOMIC);
	if (!pWb35Tx->Tx2Urb)
	{
		usb_free_urb( pWb35Tx->Tx4Urb );
		return false;
	}

	return true;
}