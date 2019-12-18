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
typedef  int /*<<< orphan*/  u8_t ;
typedef  int /*<<< orphan*/  u32_t ;

/* Variables and functions */
 int /*<<< orphan*/  zfLnxInitUsbRxQ (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfLnxInitUsbTxQ (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfLnxSubmitRegInUrb (int /*<<< orphan*/ *) ; 

u32_t zfwUsbEnableIntEpt(zdev_t *dev, u8_t endpt)
{
    /* Initialize USB TxQ */
    zfLnxInitUsbTxQ(dev);

    /* Initialize USB RxQ */
    zfLnxInitUsbRxQ(dev);

    /* Initialize USB Register In URB */
    //zfwUsbSubmitRegIn(dev);
    /* Initialize USB Register In URB */
    zfLnxSubmitRegInUrb(dev);

    return 0;
}