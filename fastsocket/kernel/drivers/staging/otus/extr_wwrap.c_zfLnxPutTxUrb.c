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
typedef  int u16_t ;
struct usbdrv_private {int TxUrbHead; int TxUrbCnt; int /*<<< orphan*/  cs_lock; int /*<<< orphan*/  TxUrbTail; } ;

/* Variables and functions */
 int ZM_MAX_TX_URB_NUM ; 
 int /*<<< orphan*/  printk (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void zfLnxPutTxUrb(zdev_t *dev)
{
    struct usbdrv_private *macp = dev->ml_priv;
    u16_t idx;
    unsigned long irqFlag;

    spin_lock_irqsave(&macp->cs_lock, irqFlag);

    idx = ((macp->TxUrbHead + 1) & (ZM_MAX_TX_URB_NUM - 1));

    //if (idx != macp->TxUrbTail)
    if (macp->TxUrbCnt < ZM_MAX_TX_URB_NUM)
    {
        macp->TxUrbHead = idx;
        macp->TxUrbCnt++;
    }
    else
    {
        printk("UsbTxUrbQ inconsistent: TxUrbHead: %d, TxUrbTail: %d\n",
                macp->TxUrbHead, macp->TxUrbTail);
    }

    spin_unlock_irqrestore(&macp->cs_lock, irqFlag);
}