#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
struct TYPE_3__ {int /*<<< orphan*/ * context; } ;
typedef  TYPE_1__ urb_t ;

/* Variables and functions */
 scalar_t__ zfLnxCheckTxBufferCnt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfLnxPutTxUrb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfLnxUsbSubmitTxData (int /*<<< orphan*/ *) ; 

void zfLnxUsbDataOut_callback(urb_t *urb)
{
    zdev_t* dev = urb->context;
    //UsbTxQ_t *TxData;

    /* Give the urb back */
    zfLnxPutTxUrb(dev);

    /* Check whether there is any pending buffer needed */
    /* to be sent */
    if (zfLnxCheckTxBufferCnt(dev) != 0)
    {
        //TxData = zfwGetUsbTxBuffer(dev);

        //if (TxData == NULL)
        //{
        //    printk("Get a NULL buffer from zfwGetUsbTxBuffer\n");
        //    return;
        //}
        //else
        //{
            zfLnxUsbSubmitTxData(dev);
        //}
    }
}