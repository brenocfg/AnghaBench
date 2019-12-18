#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
typedef  int /*<<< orphan*/  zbuf_t ;
typedef  size_t u8_t ;
typedef  scalar_t__ u32_t ;
typedef  scalar_t__ u16_t ;
struct dest {scalar_t__ Qtype; void* vtxq; TYPE_1__* tid_tx; } ;
typedef  scalar_t__ s8_t ;
struct TYPE_9__ {size_t ppri; struct dest* (* getNext ) (int /*<<< orphan*/ *,size_t) ;scalar_t__* Head; } ;
struct TYPE_8__ {scalar_t__ txq_threshold; int destLock; scalar_t__ aggState; int /*<<< orphan*/  aggInitiated; } ;
struct TYPE_7__ {int /*<<< orphan*/  size; int /*<<< orphan*/  aggTail; int /*<<< orphan*/  aggHead; } ;
typedef  TYPE_1__* TID_TX ;

/* Variables and functions */
 scalar_t__ AGG_MIN_TXQL ; 
 TYPE_6__ DESTQ ; 
 int /*<<< orphan*/  DbgPrint (char*) ; 
 scalar_t__ TXQL ; 
 int /*<<< orphan*/  ZM_EXTERNAL_ALLOC_BUF ; 
 size_t* pri ; 
 struct dest* stub1 (int /*<<< orphan*/ *,size_t) ; 
 TYPE_5__* wd ; 
 TYPE_1__* zfAggTxReady (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfAggTxSend (int /*<<< orphan*/ *,int,TYPE_1__*) ; 
 scalar_t__ zfAggValidTidTx (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * zfGetVtxq (int /*<<< orphan*/ *,size_t) ; 
 int zfHpGetFreeTxdCount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfTxSendEth (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zm_agg_qlen (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zm_assert (int) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

void    zfAggTxScheduler(zdev_t* dev, u8_t ScanAndClear)
{
    TID_TX  tid_tx = NULL;
    void*   vtxq;
    struct dest* dest;
    zbuf_t*  buf;
    u32_t txql, min_txql;
    //u16_t aggr_size = 1;
    u16_t txq_threshold;
    zmw_get_wlan_dev(dev);

    zmw_declare_for_critical_section();

    if (!wd->aggInitiated)
    {
        return;
    }

    /* debug */
    txql = TXQL;
    min_txql = AGG_MIN_TXQL;

    if(wd->txq_threshold)
        txq_threshold = wd->txq_threshold;
    else
        txq_threshold = AGG_MIN_TXQL;

    tid_tx = zfAggTxReady(dev);
    if (tid_tx) ScanAndClear = 0;
    while (zfHpGetFreeTxdCount(dev) > 20 && (TXQL < txq_threshold || tid_tx)) {
    //while (zfHpGetFreeTxdCount(dev) > 20 && (ScanAndClear || tid_tx)) {
    //while (TXQL < txq_threshold) {
        u16_t i;
        u8_t ac;
        s8_t destQ_count = 0;
    //while ((zfHpGetFreeTxdCount(dev)) > 32) {

        //DbgPrint("zfAggTxScheduler: in while loop");
        for (i=0; i<4; i++) {
            if (DESTQ.Head[i]) destQ_count++;
        }
        if (0 >= destQ_count) break;

        zmw_enter_critical_section(dev);
        ac = pri[DESTQ.ppri]; DESTQ.ppri = (DESTQ.ppri + 1) % 10;
        zmw_leave_critical_section(dev);

        for (i=0; i<10; i++){
            if(DESTQ.Head[ac]) break;

            zmw_enter_critical_section(dev);
            ac = pri[DESTQ.ppri]; DESTQ.ppri = (DESTQ.ppri + 1) % 10;
            zmw_leave_critical_section(dev);
        }
        if (i == 10) break;
        //DbgPrint("zfAggTxScheduler: have dest Q");
        zmw_enter_critical_section(dev);
        wd->destLock = 1;
        zmw_leave_critical_section(dev);

        dest = DESTQ.getNext(dev, ac);
        if (!dest) {
            zmw_enter_critical_section(dev);
            wd->destLock = 0;
            zmw_leave_critical_section(dev);

            DbgPrint("bug report! DESTQ.getNext got nothing!");
            break;
        }
        if (dest->Qtype == 0) {
            tid_tx = dest->tid_tx;

            //DbgPrint("zfAggTxScheduler: have tid_tx Q");

            if(tid_tx && zfAggValidTidTx(dev, tid_tx))
                tid_tx->size = zm_agg_qlen(dev, tid_tx->aggHead, tid_tx->aggTail);
            else {
                zmw_enter_critical_section(dev);
                wd->destLock = 0;
                zmw_leave_critical_section(dev);

                tid_tx = zfAggTxReady(dev);
                continue;
            }

            zmw_enter_critical_section(dev);
            wd->destLock = 0;
            zmw_leave_critical_section(dev);
            //zmw_enter_critical_section(dev);
            if (tid_tx && !tid_tx->size) {

                //zmw_leave_critical_section(dev);
                //DESTQ.delete(dev, 0, tid_tx, NULL);
            }
            else if(wd->aggState == 0){
                //wd->aggState = 1;
                //zmw_leave_critical_section(dev);
                zfAggTxSend(dev, zfHpGetFreeTxdCount(dev), tid_tx);
                //wd->aggState = 0;
            }
            else {
                //zmw_leave_critical_section(dev);
                break;
            }
        }
        else {
            vtxq = dest->vtxq;
            buf = zfGetVtxq(dev, ac);
            zm_assert( buf != 0 );

            zfTxSendEth(dev, buf, 0, ZM_EXTERNAL_ALLOC_BUF, 0);

        }
        /*flush all but < 16 frames in tid_tx to TXQ*/
        tid_tx = zfAggTxReady(dev);
    }

    /*while ((zfHpGetFreeTxdCount(dev)) > 32) {
    //while ((zfHpGetFreeTxdCount(dev)) > 32) {

        destQ_count = 0;
        for (i=0; i<4; i++) destQ_count += wd->destQ.size[i];
        if (0 >= destQ_count) break;

        ac = pri[wd->destQ.ppri]; wd->destQ.ppri = (wd->destQ.ppri + 1) % 10;
        for (i=0; i<10; i++){
            if(wd->destQ.size[ac]!=0) break;
            ac = pri[wd->destQ.ppri]; wd->destQ.ppri = (wd->destQ.ppri + 1) % 10;
        }
        if (i == 10) break;
        dest = wd->destQ.getNext(dev, ac);
        if (dest->Qtype == 0) {
            tid_tx = dest->tid_tx;
            tid_tx->size = zm_agg_qlen(dev, tid_tx->aggHead, tid_tx->aggTail);
            if (!tid_tx->size) {
                wd->destQ.delete(dev, 0, tid_tx, NULL);
                break;
            }
            else if((wd->aggState == 0) && (tid_tx->size >= 16)){
                zfAggTxSend(dev, zfHpGetFreeTxdCount(dev), tid_tx);
            }
            else {
                break;
            }
        }

    }
    */
    return;
}