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
struct TYPE_4__ {int /*<<< orphan*/  dwIsrRxNoBuf; int /*<<< orphan*/  dwIsrMIBNearfull; int /*<<< orphan*/  dwIsrSoftInterrupt; int /*<<< orphan*/  dwIsrUnrecoverableError; int /*<<< orphan*/  dwIsrWatchDog; int /*<<< orphan*/  dwIsrSTIMERInt; int /*<<< orphan*/  dwIsrTBTTInt; int /*<<< orphan*/  dwIsrRx0OK; int /*<<< orphan*/  dwIsrBeaconTxOK; int /*<<< orphan*/  dwIsrTx0OK; int /*<<< orphan*/  dwIsrUnknown; } ;
struct TYPE_5__ {TYPE_1__ ISRStat; } ;
typedef  TYPE_2__* PSStatCounter ;
typedef  int BYTE ;

/* Variables and functions */
 int ISR_ACTX ; 
 int ISR_BNTX ; 
 int ISR_FETALERR ; 
 int ISR_MIBNEARFULL ; 
 int ISR_RXDMA0 ; 
 int ISR_RXNOBUF ; 
 int ISR_SOFTINT ; 
 int ISR_SOFTTIMER ; 
 int ISR_TBTT ; 
 int ISR_WATCHDOG ; 

void STAvUpdateIsrStatCounter (PSStatCounter pStatistic, BYTE byIsr0, BYTE byIsr1)
{
    /**********************/
    /* ABNORMAL interrupt */
    /**********************/
    // not any IMR bit invoke irq
    if (byIsr0 == 0) {
        pStatistic->ISRStat.dwIsrUnknown++;
        return;
    }


    if (byIsr0 & ISR_ACTX)              // ISR, bit0
        pStatistic->ISRStat.dwIsrTx0OK++;           // TXDMA0 successful

    if (byIsr0 & ISR_BNTX)              // ISR, bit2
        pStatistic->ISRStat.dwIsrBeaconTxOK++;      // BeaconTx successful

    if (byIsr0 & ISR_RXDMA0)            // ISR, bit3
        pStatistic->ISRStat.dwIsrRx0OK++;           // Rx0 successful

    if (byIsr0 & ISR_TBTT)              // ISR, bit4
        pStatistic->ISRStat.dwIsrTBTTInt++;         // TBTT successful

    if (byIsr0 & ISR_SOFTTIMER)         // ISR, bit6
        pStatistic->ISRStat.dwIsrSTIMERInt++;

    if (byIsr0 & ISR_WATCHDOG)          // ISR, bit7
        pStatistic->ISRStat.dwIsrWatchDog++;


    if (byIsr1 & ISR_FETALERR)              // ISR, bit8
        pStatistic->ISRStat.dwIsrUnrecoverableError++;

    if (byIsr1 & ISR_SOFTINT)               // ISR, bit9
        pStatistic->ISRStat.dwIsrSoftInterrupt++;       // software interrupt

    if (byIsr1 & ISR_MIBNEARFULL)           // ISR, bit10
        pStatistic->ISRStat.dwIsrMIBNearfull++;

    if (byIsr1 & ISR_RXNOBUF)               // ISR, bit11
        pStatistic->ISRStat.dwIsrRxNoBuf++;             // Rx No Buff

}