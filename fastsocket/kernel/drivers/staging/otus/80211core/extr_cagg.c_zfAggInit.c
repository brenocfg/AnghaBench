#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
typedef  size_t u16_t ;
struct baw_enabler {int dummy; } ;
struct agg_tid_rx {int dummy; } ;
struct aggQueue {int dummy; } ;
struct TYPE_14__ {int /*<<< orphan*/  (* init ) (int /*<<< orphan*/ *) ;} ;
struct TYPE_13__ {int /*<<< orphan*/  (* init ) (int /*<<< orphan*/ *) ;} ;
struct TYPE_12__ {int aggInitiated; int reorder; TYPE_4__** tid_rx; TYPE_2__** aggQPool; scalar_t__ aggState; TYPE_1__* aggSta; scalar_t__ addbaCount; scalar_t__ addbaComplete; } ;
struct TYPE_11__ {size_t aid; scalar_t__ addBaExchangeStatusCode; TYPE_3__* frame; scalar_t__ sq_behind_count; scalar_t__ sq_exceed_count; scalar_t__ baw_tail; scalar_t__ baw_head; scalar_t__ seq_start; } ;
struct TYPE_10__ {scalar_t__ buf; } ;
struct TYPE_9__ {scalar_t__ deleteFlag; scalar_t__ clearFlag; scalar_t__ aggReady; scalar_t__ aggQEnabled; scalar_t__ aggTail; scalar_t__ aggHead; } ;
struct TYPE_8__ {int /*<<< orphan*/ ** tid_tx; scalar_t__* count; scalar_t__* aggFlag; } ;

/* Variables and functions */
 TYPE_7__* BAW ; 
 TYPE_6__ DESTQ ; 
 size_t ZM_AC ; 
 size_t ZM_AGG_BAW_SIZE ; 
 size_t ZM_AGG_POOL_SIZE ; 
 size_t ZM_MAX_STA_SUPPORT ; 
 scalar_t__ aggr_count ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *) ; 
 scalar_t__ success_mpdu ; 
 scalar_t__ total_mpdu ; 
 TYPE_5__* wd ; 
 int /*<<< orphan*/  zfAggDestInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfAggTallyReset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfBawInit (int /*<<< orphan*/ *) ; 
 void* zfwMemAllocate (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

void zfAggInit(zdev_t* dev)
{
    u16_t i,j;

    zmw_get_wlan_dev(dev);

    zmw_declare_for_critical_section();
    /*
     * reset sta information
     */

    zmw_enter_critical_section(dev);
    wd->aggInitiated = 0;
    wd->addbaComplete = 0;
    wd->addbaCount = 0;
    wd->reorder = 1;
    for (i=0; i<ZM_MAX_STA_SUPPORT; i++)
    {
        for (j=0; j<ZM_AC; j++)
        {
            //wd->aggSta[i].aggQNumber[j] = ZM_AGG_POOL_SIZE;
            wd->aggSta[i].aggFlag[j] = wd->aggSta[i].count[j] = 0;
            wd->aggSta[i].tid_tx[j] = NULL;
            wd->aggSta[i].tid_tx[j+1] = NULL;

        }
    }

    /*
     * reset Tx/Rx aggregation queue information
     */
    wd->aggState = 0;
    for (i=0; i<ZM_AGG_POOL_SIZE; i++)
    {
        /*
         * reset tx aggregation queue
         */
        wd->aggQPool[i] = zfwMemAllocate(dev, sizeof(struct aggQueue));
        if(!wd->aggQPool[i])
        {
            zmw_leave_critical_section(dev);
            return;
        }
        wd->aggQPool[i]->aggHead = wd->aggQPool[i]->aggTail =
        wd->aggQPool[i]->aggQEnabled = wd->aggQPool[i]->aggReady =
        wd->aggQPool[i]->clearFlag = wd->aggQPool[i]->deleteFlag = 0;
        //wd->aggQPool[i]->aggSize = 16;

        /*
         * reset rx aggregation queue
         */
        wd->tid_rx[i] = zfwMemAllocate(dev, sizeof(struct agg_tid_rx));
        if (!wd->tid_rx[i])
        {
            zmw_leave_critical_section(dev);
            return;
        }
        wd->tid_rx[i]->aid = ZM_MAX_STA_SUPPORT;
        wd->tid_rx[i]->seq_start = wd->tid_rx[i]->baw_head = \
        wd->tid_rx[i]->baw_tail = 0;
        wd->tid_rx[i]->sq_exceed_count = wd->tid_rx[i]->sq_behind_count = 0;
        for (j=0; j<=ZM_AGG_BAW_SIZE; j++)
            wd->tid_rx[i]->frame[j].buf = 0;
        /*
         * reset ADDBA exchange status code
         * 0: NULL
         * 1: ADDBA Request sent/received
         * 2: ACK for ADDBA Request sent/received
         * 3: ADDBA Response sent/received
         * 4: ACK for ADDBA Response sent/received
         */
        wd->tid_rx[i]->addBaExchangeStatusCode = 0;

    }
    zmw_leave_critical_section(dev);
    zfAggTallyReset(dev);
    DESTQ.init = zfAggDestInit;
    DESTQ.init(dev);
    wd->aggInitiated = 1;
    aggr_count = 0;
    success_mpdu = 0;
    total_mpdu = 0;
#ifdef ZM_ENABLE_AGGREGATION
#ifndef ZM_ENABLE_FW_BA_RETRANSMISSION //disable BAW
    BAW = zfwMemAllocate(dev, sizeof(struct baw_enabler));
    if(!BAW)
    {
        return;
    }
    BAW->init = zfBawInit;
    BAW->init(dev);
#endif //disable BAW
#endif
}