#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
struct aggBarControl {int /*<<< orphan*/  tid_info; scalar_t__ compressed_bitmap; scalar_t__ multi_tid; scalar_t__ bar_ack_policy; } ;
struct TYPE_4__ {int /*<<< orphan*/  tid; } ;
typedef  TYPE_1__* TID_TX ;

/* Variables and functions */
 int /*<<< orphan*/  zfAggSendBar (int /*<<< orphan*/ *,TYPE_1__*,struct aggBarControl*) ; 

void   zfAggInvokeBar(zdev_t* dev, TID_TX tid_tx)
{
    struct aggBarControl aggBarControl;
    //zmw_get_wlan_dev(dev);

    //zmw_declare_for_critical_section();
    //bar_control = aggBarControl->tid_info << 12 | aggBarControl->compressed_bitmap << 2
    //        | aggBarControl->multi_tid << 1 | aggBarControl->bar_ack_policy;
    aggBarControl.bar_ack_policy = 0;
    aggBarControl.multi_tid = 0;
    aggBarControl.compressed_bitmap = 0;
    aggBarControl.tid_info = tid_tx->tid;
    zfAggSendBar(dev, tid_tx, &aggBarControl);

    return;

}