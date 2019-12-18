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
struct TYPE_4__ {int /*<<< orphan*/  dwIsrSTIMER1Int; int /*<<< orphan*/  dwIsrRx1OK; int /*<<< orphan*/  dwIsrRxNoBuf; int /*<<< orphan*/  dwIsrMIBNearfull; int /*<<< orphan*/  dwIsrSoftInterrupt; int /*<<< orphan*/  dwIsrUnrecoverableError; int /*<<< orphan*/  dwIsrWatchDog; int /*<<< orphan*/  dwIsrSTIMERInt; int /*<<< orphan*/  dwIsrTBTTInt; int /*<<< orphan*/  dwIsrRx0OK; int /*<<< orphan*/  dwIsrBeaconTxOK; int /*<<< orphan*/  dwIsrAC0TxOK; int /*<<< orphan*/  dwIsrTx0OK; int /*<<< orphan*/  dwIsrUnknown; } ;
struct TYPE_5__ {TYPE_1__ ISRStat; } ;
typedef  TYPE_2__* PSStatCounter ;
typedef  int DWORD ;

/* Variables and functions */
 int ISR_AC0DMA ; 
 int ISR_BNTX ; 
 int ISR_FETALERR ; 
 int ISR_MIBNEARFULL ; 
 int ISR_RXDMA0 ; 
 int ISR_RXDMA1 ; 
 int ISR_RXNOBUF ; 
 int ISR_SOFTINT ; 
 int ISR_SOFTTIMER ; 
 int ISR_SOFTTIMER1 ; 
 int ISR_TBTT ; 
 int ISR_TXDMA0 ; 
 int ISR_WATCHDOG ; 

void STAvUpdateIsrStatCounter (PSStatCounter pStatistic, DWORD dwIsr)
{
    /**********************/
    /* ABNORMAL interrupt */
    /**********************/
    // not any IMR bit invoke irq

    if (dwIsr == 0) {
        pStatistic->ISRStat.dwIsrUnknown++;
        return;
    }

//Added by Kyle
    if (dwIsr & ISR_TXDMA0)               // ISR, bit0
        pStatistic->ISRStat.dwIsrTx0OK++;             // TXDMA0 successful

    if (dwIsr & ISR_AC0DMA)               // ISR, bit1
        pStatistic->ISRStat.dwIsrAC0TxOK++;           // AC0DMA successful

    if (dwIsr & ISR_BNTX)                 // ISR, bit2
        pStatistic->ISRStat.dwIsrBeaconTxOK++;        // BeaconTx successful

    if (dwIsr & ISR_RXDMA0)               // ISR, bit3
        pStatistic->ISRStat.dwIsrRx0OK++;             // Rx0 successful

    if (dwIsr & ISR_TBTT)                 // ISR, bit4
        pStatistic->ISRStat.dwIsrTBTTInt++;           // TBTT successful

    if (dwIsr & ISR_SOFTTIMER)            // ISR, bit6
        pStatistic->ISRStat.dwIsrSTIMERInt++;

    if (dwIsr & ISR_WATCHDOG)             // ISR, bit7
        pStatistic->ISRStat.dwIsrWatchDog++;

    if (dwIsr & ISR_FETALERR)             // ISR, bit8
        pStatistic->ISRStat.dwIsrUnrecoverableError++;

    if (dwIsr & ISR_SOFTINT)              // ISR, bit9
        pStatistic->ISRStat.dwIsrSoftInterrupt++;     // software interrupt

    if (dwIsr & ISR_MIBNEARFULL)          // ISR, bit10
        pStatistic->ISRStat.dwIsrMIBNearfull++;

    if (dwIsr & ISR_RXNOBUF)              // ISR, bit11
        pStatistic->ISRStat.dwIsrRxNoBuf++;           // Rx No Buff

    if (dwIsr & ISR_RXDMA1)               // ISR, bit12
        pStatistic->ISRStat.dwIsrRx1OK++;             // Rx1 successful

//    if (dwIsr & ISR_ATIMTX)               // ISR, bit13
//        pStatistic->ISRStat.dwIsrATIMTxOK++;          // ATIMTX successful

//    if (dwIsr & ISR_SYNCTX)               // ISR, bit14
//        pStatistic->ISRStat.dwIsrSYNCTxOK++;          // SYNCTX successful

//    if (dwIsr & ISR_CFPEND)               // ISR, bit18
//        pStatistic->ISRStat.dwIsrCFPEnd++;

//    if (dwIsr & ISR_ATIMEND)              // ISR, bit19
//        pStatistic->ISRStat.dwIsrATIMEnd++;

//    if (dwIsr & ISR_SYNCFLUSHOK)          // ISR, bit20
//        pStatistic->ISRStat.dwIsrSYNCFlushOK++;

    if (dwIsr & ISR_SOFTTIMER1)           // ISR, bit21
        pStatistic->ISRStat.dwIsrSTIMER1Int++;

}