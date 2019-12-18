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
struct wb35_rx {int /*<<< orphan*/  RxUrb; } ;
struct hw_data {struct wb35_rx Wb35Rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  Wb35Rx_reset_descriptor (struct hw_data*) ; 
 int /*<<< orphan*/  usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

unsigned char Wb35Rx_initial(struct hw_data * pHwData)
{
	struct wb35_rx *pWb35Rx = &pHwData->Wb35Rx;

	// Initial the Buffer Queue
	Wb35Rx_reset_descriptor( pHwData );

	pWb35Rx->RxUrb = usb_alloc_urb(0, GFP_ATOMIC);
	return (!!pWb35Rx->RxUrb);
}