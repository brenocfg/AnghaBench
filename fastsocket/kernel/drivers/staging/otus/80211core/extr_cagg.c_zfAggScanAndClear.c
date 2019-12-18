#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
typedef  scalar_t__ u32_t ;
typedef  size_t u16_t ;
struct TYPE_6__ {scalar_t__ state; int tick; TYPE_2__** aggQPool; } ;
struct TYPE_5__ {int aggQEnabled; size_t aggHead; size_t aggTail; int clearFlag; scalar_t__ lastArrival; int /*<<< orphan*/  size; TYPE_1__* aggvtxq; } ;
struct TYPE_4__ {scalar_t__ arrivalTime; } ;
typedef  TYPE_2__* TID_TX ;

/* Variables and functions */
 scalar_t__ ZM_AGG_CLEAR_TIME ; 
 scalar_t__ ZM_AGG_DELETE_TIME ; 
 size_t ZM_AGG_POOL_SIZE ; 
 int /*<<< orphan*/  ZM_LV_0 ; 
 size_t ZM_SUCCESS ; 
 scalar_t__ ZM_WLAN_STATE_ENABLED ; 
 TYPE_3__* wd ; 
 int /*<<< orphan*/  zfAggPrintTally (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfAggRxClear (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  zfAggTxDeleteQueue (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  zfAggTxScheduler (int /*<<< orphan*/ *,int) ; 
 scalar_t__ zm_agg_GetTime () ; 
 int /*<<< orphan*/  zm_agg_qlen (int /*<<< orphan*/ *,size_t,size_t) ; 
 int /*<<< orphan*/  zm_msg1_agg (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

u16_t   zfAggScanAndClear(zdev_t* dev, u32_t time)
{
    u16_t i;
    u16_t head;
    u16_t tail;
    u32_t tick;
    u32_t arrivalTime;
    //u16_t aid, ac;
    TID_TX tid_tx;

    zmw_get_wlan_dev(dev);

    zmw_declare_for_critical_section();

    if(!(wd->state == ZM_WLAN_STATE_ENABLED)) return 0;
    zfAggTxScheduler(dev, 1);
    tick = zm_agg_GetTime();
    for (i=0; i<ZM_AGG_POOL_SIZE; i++)
    {
        if (!wd->aggQPool[i]) return 0;
        if (1 == wd->aggQPool[i]->aggQEnabled)
        {
            tid_tx = wd->aggQPool[i];
            zmw_enter_critical_section(dev);

            head = tid_tx->aggHead;
            tail = tid_tx->aggTail;

            arrivalTime = (u32_t)tid_tx->aggvtxq[tid_tx->aggTail].arrivalTime;


            if((tick - arrivalTime) <= ZM_AGG_CLEAR_TIME)
            {

            }
            else if((tid_tx->size = zm_agg_qlen(dev, tid_tx->aggHead, tid_tx->aggTail)) > 0)
            {

                tid_tx->clearFlag = 1;

                //zm_msg1_agg(ZM_LV_0, "clear queue    tick =", tick);
                //zm_msg1_agg(ZM_LV_0, "clear queue arrival =", arrivalTime);


                //zmw_leave_critical_section(dev);
                //zfAggTxScheduler(dev);
                //zmw_enter_critical_section(dev);

            }

            if (tid_tx->size == 0)
            {
                /*
                 * queue empty
                 */
                if (tick - tid_tx->lastArrival > ZM_AGG_DELETE_TIME)
                {
                    zm_msg1_agg(ZM_LV_0, "delete queue, idle for n sec. n = ", \
                            ZM_AGG_DELETE_TIME/10);

                    zmw_leave_critical_section(dev);
                    zfAggTxDeleteQueue(dev, i);
                    zmw_enter_critical_section(dev);
                }
            }

            zmw_leave_critical_section(dev);
        }
    }

        zfAggRxClear(dev, time);

#ifdef ZM_AGG_TALLY
    if((wd->tick % 100) == 0) {
        zfAggPrintTally(dev);
    }
#endif

    return ZM_SUCCESS;
}