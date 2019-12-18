#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
typedef  int /*<<< orphan*/  zbuf_t ;
struct TYPE_5__ {size_t aggHead; size_t aggTail; scalar_t__ size; TYPE_1__* aggvtxq; } ;
struct TYPE_4__ {int /*<<< orphan*/ * buf; } ;
typedef  TYPE_2__* TID_TX ;

/* Variables and functions */
 int ZM_AGGQ_SIZE_MASK ; 
 int /*<<< orphan*/  ZM_LV_0 ; 
 scalar_t__ zm_agg_qlen (int /*<<< orphan*/ *,size_t,int) ; 
 int /*<<< orphan*/  zm_msg1_agg (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

zbuf_t* zfAggTxGetVtxq(zdev_t* dev, TID_TX tid_tx)
{
    zbuf_t* buf = NULL;

    zmw_declare_for_critical_section();

    if (tid_tx->aggHead != tid_tx->aggTail)
    {
        buf = tid_tx->aggvtxq[ tid_tx->aggTail ].buf;

        tid_tx->aggvtxq[tid_tx->aggTail].buf = NULL;

        zmw_enter_critical_section(dev);
        tid_tx->aggTail = ((tid_tx->aggTail + 1) & ZM_AGGQ_SIZE_MASK);
        if(tid_tx->size > 0) tid_tx->size--;
        tid_tx->size = zm_agg_qlen(dev, tid_tx->aggHead, tid_tx->aggTail);
        if (NULL == buf) {
            //tid_tx->aggTail = tid_tx->aggHead = tid_tx->size = 0;
            //zm_msg1_agg(ZM_LV_0, "GetVtxq buf == NULL, tid_tx->size=", tid_tx->size);
        }
        zmw_leave_critical_section(dev);
    }
    else
    {
        /*
         * queue is empty
         */
        zm_msg1_agg(ZM_LV_0, "tid_tx->aggHead == tid_tx->aggTail, tid_tx->size=", tid_tx->size);

    }

    if (zm_agg_qlen(dev, tid_tx->aggHead, tid_tx->aggTail) != tid_tx->size)
        zm_msg1_agg(ZM_LV_0, "qlen!=tid_tx->size! tid_tx->size=", tid_tx->size);
    return buf;
}