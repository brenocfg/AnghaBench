#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  ullTsrAllOK; } ;
struct TYPE_7__ {int dwTsrTotalRetry; int* dwTxFail; int /*<<< orphan*/  dwTsrDirected; TYPE_2__* abyTxPktInfo; int /*<<< orphan*/  dwTsrMulticast; int /*<<< orphan*/  dwTsrBroadcast; int /*<<< orphan*/  dwTsrTransmitTimeout; int /*<<< orphan*/  dwTsrRetryTimeout; int /*<<< orphan*/  dwTsrErr; int /*<<< orphan*/  TxFailCount; int /*<<< orphan*/  ullTxDirectedBytes; int /*<<< orphan*/  ullTxDirectedFrames; int /*<<< orphan*/  ullTxMulticastBytes; int /*<<< orphan*/  ullTxMulticastFrames; int /*<<< orphan*/  ullTxBroadcastBytes; int /*<<< orphan*/  ullTxBroadcastFrames; int /*<<< orphan*/ * dwTxOk; TYPE_1__ CustomStat; int /*<<< orphan*/  ullTsrOK; int /*<<< orphan*/  TxRetryOkCount; int /*<<< orphan*/  TxNoRetryOkCount; int /*<<< orphan*/ * dwTxRetryCount; int /*<<< orphan*/  dwTsrMoreThanOnceRetry; int /*<<< orphan*/  dwTsrOnceRetry; int /*<<< orphan*/  dwTsrRetry; int /*<<< orphan*/  dwTsrTxPacket; } ;
struct TYPE_6__ {scalar_t__ byBroadMultiUni; scalar_t__ wLength; } ;
typedef  TYPE_3__* PSStatCounter ;
typedef  int BYTE ;

/* Variables and functions */
 size_t MAX_RATE ; 
 int TSR_RETRYTMO ; 
 int TSR_TMO ; 
 scalar_t__ TX_PKT_BROAD ; 
 scalar_t__ TX_PKT_MULTI ; 
 scalar_t__ TX_PKT_UNI ; 

void
STAvUpdateTDStatCounter (
    PSStatCounter   pStatistic,
    BYTE            byPktNum,
    BYTE            byRate,
    BYTE            byTSR
    )
{
    BYTE    byRetyCnt;
    // increase tx packet count
    pStatistic->dwTsrTxPacket++;

    byRetyCnt = (byTSR & 0xF0) >> 4;
    if (byRetyCnt != 0) {
        pStatistic->dwTsrRetry++;
        pStatistic->dwTsrTotalRetry += byRetyCnt;
        pStatistic->dwTxFail[byRate]+= byRetyCnt;
        pStatistic->dwTxFail[MAX_RATE] += byRetyCnt;

        if ( byRetyCnt == 0x1)
            pStatistic->dwTsrOnceRetry++;
        else
            pStatistic->dwTsrMoreThanOnceRetry++;

        if (byRetyCnt <= 8)
            pStatistic->dwTxRetryCount[byRetyCnt-1]++;

    }
    if ( !(byTSR & (TSR_TMO | TSR_RETRYTMO))) {

#ifdef Calcu_LinkQual
   if (byRetyCnt < 2)
        pStatistic->TxNoRetryOkCount ++;
   else
        pStatistic->TxRetryOkCount ++;
#endif

        pStatistic->ullTsrOK++;
        pStatistic->CustomStat.ullTsrAllOK++;
        // update counters in case that successful transmit
        pStatistic->dwTxOk[byRate]++;
        pStatistic->dwTxOk[MAX_RATE]++;

        if ( pStatistic->abyTxPktInfo[byPktNum].byBroadMultiUni == TX_PKT_BROAD )  {
            pStatistic->ullTxBroadcastFrames++;
            pStatistic->ullTxBroadcastBytes += pStatistic->abyTxPktInfo[byPktNum].wLength;
        } else if ( pStatistic->abyTxPktInfo[byPktNum].byBroadMultiUni == TX_PKT_MULTI ) {
            pStatistic->ullTxMulticastFrames++;
            pStatistic->ullTxMulticastBytes += pStatistic->abyTxPktInfo[byPktNum].wLength;
        } else if ( pStatistic->abyTxPktInfo[byPktNum].byBroadMultiUni == TX_PKT_UNI ) {
            pStatistic->ullTxDirectedFrames++;
            pStatistic->ullTxDirectedBytes += pStatistic->abyTxPktInfo[byPktNum].wLength;
        }
    }
    else {

#ifdef Calcu_LinkQual
        pStatistic->TxFailCount ++;
#endif

        pStatistic->dwTsrErr++;
        if (byTSR & TSR_RETRYTMO)
            pStatistic->dwTsrRetryTimeout++;
        if (byTSR & TSR_TMO)
            pStatistic->dwTsrTransmitTimeout++;
    }

    if ( pStatistic->abyTxPktInfo[byPktNum].byBroadMultiUni == TX_PKT_BROAD )  {
        pStatistic->dwTsrBroadcast++;
    } else if ( pStatistic->abyTxPktInfo[byPktNum].byBroadMultiUni == TX_PKT_MULTI ) {
        pStatistic->dwTsrMulticast++;
    } else if ( pStatistic->abyTxPktInfo[byPktNum].byBroadMultiUni == TX_PKT_UNI ) {
        pStatistic->dwTsrDirected++;
    }
}