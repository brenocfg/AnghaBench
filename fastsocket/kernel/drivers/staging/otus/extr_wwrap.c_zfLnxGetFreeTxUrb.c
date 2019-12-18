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
struct usbdrv_private {scalar_t__ TxUrbCnt; int TxUrbTail; int /*<<< orphan*/  cs_lock; } ;

/* Variables and functions */
 int ZM_MAX_TX_URB_NUM ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

u16_t zfLnxGetFreeTxUrb(zdev_t *dev)
{
    struct usbdrv_private *macp = dev->ml_priv;
    u16_t idx;
    unsigned long irqFlag;

    spin_lock_irqsave(&macp->cs_lock, irqFlag);

    //idx = ((macp->TxUrbTail + 1) & (ZM_MAX_TX_URB_NUM - 1));

    //if (idx != macp->TxUrbHead)
    if (macp->TxUrbCnt != 0)
    {
        idx = macp->TxUrbTail;
        macp->TxUrbTail = ((macp->TxUrbTail + 1) & (ZM_MAX_TX_URB_NUM - 1));
        macp->TxUrbCnt--;
    }
    else
    {
        //printk(KERN_ERR "macp->TxUrbCnt: %d\n", macp->TxUrbCnt);
        idx = 0xffff;
    }

    spin_unlock_irqrestore(&macp->cs_lock, irqFlag);
    return idx;
}