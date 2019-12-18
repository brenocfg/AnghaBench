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
struct TYPE_3__ {struct usbdrv_private* ml_priv; } ;
typedef  TYPE_1__ zdev_t ;
typedef  int /*<<< orphan*/  zbuf_t ;
struct usbdrv_private {scalar_t__ RxBufCnt; size_t RxBufHead; int /*<<< orphan*/  cs_lock; int /*<<< orphan*/  RxBufTail; int /*<<< orphan*/ ** UsbRxBufQ; } ;

/* Variables and functions */
 int ZM_MAX_RX_URB_NUM ; 
 int /*<<< orphan*/  printk (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

zbuf_t *zfLnxGetUsbRxBuffer(zdev_t *dev)
{
    struct usbdrv_private *macp = dev->ml_priv;
    //u16_t idx;
    zbuf_t *buf;
    unsigned long irqFlag;

    spin_lock_irqsave(&macp->cs_lock, irqFlag);

    //idx = ((macp->RxBufHead+1) & (ZM_MAX_RX_URB_NUM - 1));

    //if (idx != macp->RxBufTail)
    if (macp->RxBufCnt != 0)
    {
        buf = macp->UsbRxBufQ[macp->RxBufHead];
        macp->RxBufHead = ((macp->RxBufHead+1) & (ZM_MAX_RX_URB_NUM - 1));
        macp->RxBufCnt--;
    }
    else
    {
        printk("RxBufQ inconsistent: RxBufHead: %d, RxBufTail: %d\n",
                macp->RxBufHead, macp->RxBufTail);
        spin_unlock_irqrestore(&macp->cs_lock, irqFlag);
        return NULL;
    }

    spin_unlock_irqrestore(&macp->cs_lock, irqFlag);
    return buf;
}