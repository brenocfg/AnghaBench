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
typedef  scalar_t__ ULONGLONG ;
typedef  size_t UINT ;
struct TYPE_5__ {scalar_t__ ullTsrAllOK; } ;
struct TYPE_7__ {int* dwTsrTotalRetry; int /*<<< orphan*/ * dwTsrDirected; int /*<<< orphan*/ * dwTsrMulticast; int /*<<< orphan*/ * dwTsrBroadcast; int /*<<< orphan*/ * dwTsrACKData; int /*<<< orphan*/ * dwTsrTransmitTimeout; int /*<<< orphan*/ * dwTsrRetryTimeout; int /*<<< orphan*/ * dwTsrErr; int /*<<< orphan*/ * ullTxDirectedBytes; int /*<<< orphan*/ * ullTxDirectedFrames; int /*<<< orphan*/ * ullTxMulticastBytes; int /*<<< orphan*/ * ullTxMulticastFrames; int /*<<< orphan*/ * ullTxBroadcastBytes; int /*<<< orphan*/ * ullTxBroadcastFrames; scalar_t__* ullTsrOK; TYPE_1__ CustomStat; int /*<<< orphan*/ * dwTsrMoreThanOnceRetry; int /*<<< orphan*/ * dwTsrOnceRetry; int /*<<< orphan*/ * dwTsrRetry; int /*<<< orphan*/ * dwTsrTxOctet; int /*<<< orphan*/ * dwTsrTxPacket; } ;
struct TYPE_6__ {int /*<<< orphan*/ * abyAddr3; int /*<<< orphan*/ * abyAddr1; int /*<<< orphan*/  wFrameCtl; } ;
typedef  TYPE_2__* PWLAN_80211HDR_A4 ;
typedef  TYPE_3__* PSStatCounter ;
typedef  int /*<<< orphan*/ * PBYTE ;
typedef  int BYTE ;

/* Variables and functions */
 int ACK_DATA ; 
 scalar_t__ IS_BROADCAST_ADDRESS (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_MULTICAST_ADDRESS (int /*<<< orphan*/ *) ; 
 int TSR0_NCR ; 
 int TSR1_RETRYTMO ; 
 int TSR1_TERR ; 
 int TSR1_TMO ; 
 size_t TYPE_AC0DMA ; 
 size_t TYPE_TXDMA0 ; 
 scalar_t__ WLAN_GET_FC_TODS (int /*<<< orphan*/ ) ; 

void
STAvUpdateTDStatCounter (
    PSStatCounter   pStatistic,
    BYTE            byTSR0,
    BYTE            byTSR1,
    PBYTE           pbyBuffer,
    UINT            cbFrameLength,
    UINT            uIdx
    )
{
    PWLAN_80211HDR_A4   pHeader;
    PBYTE               pbyDestAddr;
    BYTE                byTSR0_NCR = byTSR0 & TSR0_NCR;



    pHeader = (PWLAN_80211HDR_A4) pbyBuffer;
    if (WLAN_GET_FC_TODS(pHeader->wFrameCtl) == 0) {
        pbyDestAddr = &(pHeader->abyAddr1[0]);
    }
    else {
        pbyDestAddr = &(pHeader->abyAddr3[0]);
    }
    // increase tx packet count
    pStatistic->dwTsrTxPacket[uIdx]++;
    pStatistic->dwTsrTxOctet[uIdx] += cbFrameLength;

    if (byTSR0_NCR != 0) {
        pStatistic->dwTsrRetry[uIdx]++;
        pStatistic->dwTsrTotalRetry[uIdx] += byTSR0_NCR;

        if (byTSR0_NCR == 1)
            pStatistic->dwTsrOnceRetry[uIdx]++;
        else
            pStatistic->dwTsrMoreThanOnceRetry[uIdx]++;
    }

    if ((byTSR1&(TSR1_TERR|TSR1_RETRYTMO|TSR1_TMO|ACK_DATA)) == 0) {
        pStatistic->ullTsrOK[uIdx]++;
        pStatistic->CustomStat.ullTsrAllOK =
            (pStatistic->ullTsrOK[TYPE_AC0DMA] + pStatistic->ullTsrOK[TYPE_TXDMA0]);
        // update counters in case that successful transmit
        if (IS_BROADCAST_ADDRESS(pbyDestAddr)) {
            pStatistic->ullTxBroadcastFrames[uIdx]++;
            pStatistic->ullTxBroadcastBytes[uIdx] += (ULONGLONG)cbFrameLength;
        }
        else if (IS_MULTICAST_ADDRESS(pbyDestAddr)) {
            pStatistic->ullTxMulticastFrames[uIdx]++;
            pStatistic->ullTxMulticastBytes[uIdx] += (ULONGLONG)cbFrameLength;
        }
        else {
            pStatistic->ullTxDirectedFrames[uIdx]++;
            pStatistic->ullTxDirectedBytes[uIdx] += (ULONGLONG)cbFrameLength;
        }
    }
    else {
        if (byTSR1 & TSR1_TERR)
            pStatistic->dwTsrErr[uIdx]++;
        if (byTSR1 & TSR1_RETRYTMO)
            pStatistic->dwTsrRetryTimeout[uIdx]++;
        if (byTSR1 & TSR1_TMO)
            pStatistic->dwTsrTransmitTimeout[uIdx]++;
        if (byTSR1 & ACK_DATA)
            pStatistic->dwTsrACKData[uIdx]++;
    }

    if (IS_BROADCAST_ADDRESS(pbyDestAddr))
        pStatistic->dwTsrBroadcast[uIdx]++;
    else if (IS_MULTICAST_ADDRESS(pbyDestAddr))
        pStatistic->dwTsrMulticast[uIdx]++;
    else
        pStatistic->dwTsrDirected[uIdx]++;

}