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
typedef  scalar_t__ u32_t ;
struct usbdrv_private {int /*<<< orphan*/  cs_lock; scalar_t__ TxBufCnt; } ;

/* Variables and functions */
 scalar_t__ ZM_MAX_TX_BUF_NUM ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

u32_t zfwUsbGetFreeTxQSize(zdev_t* dev)
{
    struct usbdrv_private *macp = dev->ml_priv;
    u32_t        freeTxQSize;
    unsigned long irqFlag;
    //zmw_declare_for_critical_section();

    //zmw_enter_critical_section(dev);
    spin_lock_irqsave(&macp->cs_lock, irqFlag);

    freeTxQSize = ZM_MAX_TX_BUF_NUM - macp->TxBufCnt;

    //zmw_leave_critical_section(dev);
    spin_unlock_irqrestore(&macp->cs_lock, irqFlag);

    return freeTxQSize;
}