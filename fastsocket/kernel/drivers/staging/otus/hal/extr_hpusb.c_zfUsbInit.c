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
typedef  int /*<<< orphan*/  zdev_t ;

/* Variables and functions */
 int /*<<< orphan*/  USB_ENDPOINT_INT_INDEX ; 
 int /*<<< orphan*/  USB_ENDPOINT_RX_INDEX ; 
 int /*<<< orphan*/  zfwUsbEnableIntEpt (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfwUsbEnableRxEpt (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void zfUsbInit(zdev_t* dev)
{
    /* Initialize Rx & INT endpoint for receiving data & interrupt */
    zfwUsbEnableRxEpt(dev, USB_ENDPOINT_RX_INDEX);
    zfwUsbEnableIntEpt(dev, USB_ENDPOINT_INT_INDEX);

    return;
}