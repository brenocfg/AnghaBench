#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
typedef  size_t u16_t ;
struct aggSta {scalar_t__* aggFlag; int /*<<< orphan*/ ** tid_tx; scalar_t__* count; } ;
struct aggQueue {size_t aggQSTA; size_t ac; size_t tid; scalar_t__ size; scalar_t__ deleteFlag; scalar_t__ clearFlag; scalar_t__ aggReady; scalar_t__ aggTail; scalar_t__ aggHead; scalar_t__ aggQEnabled; } ;
struct TYPE_2__ {struct aggSta* aggSta; struct aggQueue** aggQPool; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZM_LV_0 ; 
 size_t ZM_SUCCESS ; 
 TYPE_1__* wd ; 
 int /*<<< orphan*/  zm_msg1_agg (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

u16_t zfAggTxDeleteQueue(zdev_t* dev, u16_t qnum)
{
    u16_t ac, tid;
    struct aggQueue *tx_tid;
    struct aggSta   *agg_sta;

    zmw_get_wlan_dev(dev);

    zmw_declare_for_critical_section();

    tx_tid = wd->aggQPool[qnum];
    agg_sta = &wd->aggSta[tx_tid->aggQSTA];
    ac = tx_tid->ac;
    tid = tx_tid->tid;

    zmw_enter_critical_section(dev);

    tx_tid->aggQEnabled = 0;
    tx_tid->aggHead = tx_tid->aggTail = 0;
    tx_tid->aggReady = 0;
    tx_tid->clearFlag = tx_tid->deleteFlag = 0;
    tx_tid->size = 0;
    agg_sta->count[ac] = 0;

    agg_sta->tid_tx[tid] = NULL;
    agg_sta->aggFlag[ac] = 0;

    zmw_leave_critical_section(dev);

    zm_msg1_agg(ZM_LV_0, "queue deleted! qnum=", qnum);

    return ZM_SUCCESS;
}