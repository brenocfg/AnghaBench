#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_8__ ;
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
typedef  int /*<<< orphan*/  zbuf_t ;
typedef  int u32_t ;
typedef  int u16_t ;
struct aggControl {int aggEnabled; scalar_t__ addbaIndication; int /*<<< orphan*/  ampduIndication; } ;
struct TYPE_12__ {int /*<<< orphan*/  sent_packets_sum; } ;
struct TYPE_11__ {int aggState; int /*<<< orphan*/  (* zfcbSendCompleteIndication ) (int /*<<< orphan*/ *,scalar_t__) ;TYPE_8__ agg_tal; } ;
struct TYPE_10__ {int size; int complete; int /*<<< orphan*/  aggTail; int /*<<< orphan*/  aggHead; TYPE_1__* aggvtxq; scalar_t__ aggFrameSize; } ;
struct TYPE_9__ {scalar_t__ buf; } ;
typedef  TYPE_2__* TID_TX ;

/* Variables and functions */
 int /*<<< orphan*/  ZM_AGG_FIRST_MPDU ; 
 int /*<<< orphan*/  ZM_AGG_LAST_MPDU ; 
 int /*<<< orphan*/  ZM_AGG_MIDDLE_MPDU ; 
 int /*<<< orphan*/  ZM_EXTERNAL_ALLOC_BUF ; 
 int /*<<< orphan*/  ZM_LV_0 ; 
 TYPE_8__* agg_tal ; 
 int aggr_count ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_7__* wd ; 
 int /*<<< orphan*/ * zfAggTxGetVtxq (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  zfAggTxSendEth (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct aggControl*,TYPE_2__*) ; 
 int /*<<< orphan*/  zfTxSendEth (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ zfwBufGetSize (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ zm_agg_inQ (TYPE_2__*,int) ; 
 int zm_agg_min (int,int) ; 
 int /*<<< orphan*/  zm_agg_plus (int) ; 
 void* zm_agg_qlen (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zm_debug_msg0 (char*) ; 
 int /*<<< orphan*/  zm_msg1_agg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

u16_t zfAggTxSend(zdev_t* dev, u32_t freeTxd, TID_TX tid_tx)
{
    //u16_t   qnum;
    //u16_t   qlen;
    u16_t   j;
    //u16_t   sentcount = 0;
    zbuf_t* buf;
    struct  aggControl aggControl;
    u16_t   aggLen;
    //zbuf_t*  newBuf;
    //u16_t   bufLen;
    //TID_BAW tid_baw = NULL;
    //struct bufInfo *buf_info;

    zmw_get_wlan_dev(dev);

    zmw_declare_for_critical_section();

    //while (tid_tx->size > 0)

    zmw_enter_critical_section(dev);
    tid_tx->size = zm_agg_qlen(dev, tid_tx->aggHead, tid_tx->aggTail);
    aggLen = zm_agg_min(16, zm_agg_min(tid_tx->size, (u16_t)(freeTxd - 2)));
    zmw_leave_critical_section(dev);

            /*
             * why there have to be 2 free Txd?
             */
    if (aggLen <=0 )
        return 0;


    if (aggLen == 1) {
        buf = zfAggTxGetVtxq(dev, tid_tx);
        if (buf)
            zfTxSendEth(dev, buf, 0, ZM_EXTERNAL_ALLOC_BUF, 0);
        if (tid_tx->size == 0) {
            //DESTQ.delete(dev, 0, tid_tx, NULL);
        }

        return 1;
    }
                /*
                 * Free Txd queue is big enough to put aggregation
                 */
    zmw_enter_critical_section(dev);
    if (wd->aggState == 1) {
        zmw_leave_critical_section(dev);
        return 0;
    }
    wd->aggState = 1;
    zmw_leave_critical_section(dev);


    zm_msg1_agg(ZM_LV_0, "aggLen=", aggLen);
    tid_tx->aggFrameSize = 0;
    for (j=0; j < aggLen; j++) {
        buf = zfAggTxGetVtxq(dev, tid_tx);

        zmw_enter_critical_section(dev);
        tid_tx->size = zm_agg_qlen(dev, tid_tx->aggHead, tid_tx->aggTail);
        zmw_leave_critical_section(dev);

        if ( buf ) {
            //struct aggTally *agg_tal;
            u16_t completeIndex;

            if (0 == j) {
                aggControl.ampduIndication = ZM_AGG_FIRST_MPDU;

            }
            else if ((j == (aggLen - 1)) || tid_tx->size == 0)
            {
                aggControl.ampduIndication = ZM_AGG_LAST_MPDU;
                //wd->aggState = 0;

            }
            else
            {
                aggControl.ampduIndication = ZM_AGG_MIDDLE_MPDU;
                /* the packet is delayed more than 500 ms, drop it */

            }
            tid_tx->aggFrameSize += zfwBufGetSize(dev, buf);
            aggControl.addbaIndication = 0;
            aggControl.aggEnabled = 1;

#ifdef ZM_AGG_TALLY
            agg_tal = &wd->agg_tal;
            agg_tal->sent_packets_sum++;

#endif

            zfAggTxSendEth(dev, buf, 0, ZM_EXTERNAL_ALLOC_BUF, 0, &aggControl, tid_tx);

            zmw_enter_critical_section(dev);
            completeIndex = tid_tx->complete;
            if(zm_agg_inQ(tid_tx, tid_tx->complete))
                zm_agg_plus(tid_tx->complete);
            zmw_leave_critical_section(dev);

            if(zm_agg_inQ(tid_tx, completeIndex) && wd->zfcbSendCompleteIndication
                    && tid_tx->aggvtxq[completeIndex].buf) {
                wd->zfcbSendCompleteIndication(dev, tid_tx->aggvtxq[completeIndex].buf);
                zm_debug_msg0("in queue complete worked!");
            }

        }
        else {
            /*
             * this aggregation queue is empty
             */
            zm_msg1_agg(ZM_LV_0, "aggLen not reached, but no more frame, j=", j);

            break;
        }
    }
    zmw_enter_critical_section(dev);
    wd->aggState = 0;
    zmw_leave_critical_section(dev);

    //zm_acquire_agg_spin_lock(Adapter);
    tid_tx->size = zm_agg_qlen(dev, tid_tx->aggHead, tid_tx->aggTail);
    //zm_release_agg_spin_lock(Adapter);

    if (tid_tx->size == 0) {
        //DESTQ.delete(dev, 0, tid_tx, NULL);
    }



    //zfAggInvokeBar(dev, tid_tx);
    if(j>0) {
        aggr_count++;
        zm_msg1_agg(ZM_LV_0, "0xC2:sent 1 aggr, aggr_count=", aggr_count);
        zm_msg1_agg(ZM_LV_0, "0xC2:sent 1 aggr, aggr_size=", j);
    }
    return j;
}