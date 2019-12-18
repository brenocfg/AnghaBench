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
struct TYPE_5__ {int ChanNum; scalar_t__ ChanStat; TYPE_1__* CtlP; } ;
struct TYPE_4__ {scalar_t__ boardType; scalar_t__* AiopIO; scalar_t__ AltChanRingIndicator; scalar_t__ UPCIRingInd; } ;
typedef  TYPE_1__ CONTROLLER_t ;
typedef  TYPE_2__ CHANNEL_T ;
typedef  scalar_t__ ByteIO_t ;

/* Variables and functions */
 int DSR_ACT ; 
 scalar_t__ ROCKET_TYPE_PC104 ; 
 int* sBitMapSetTbl ; 
 int sInB (scalar_t__) ; 

__attribute__((used)) static int sGetChanRI(CHANNEL_T * ChP)
{
	CONTROLLER_t *CtlP = ChP->CtlP;
	int ChanNum = ChP->ChanNum;
	int RingInd = 0;

	if (CtlP->UPCIRingInd)
		RingInd = !(sInB(CtlP->UPCIRingInd) & sBitMapSetTbl[ChanNum]);
	else if (CtlP->AltChanRingIndicator)
		RingInd = sInB((ByteIO_t) (ChP->ChanStat + 8)) & DSR_ACT;
	else if (CtlP->boardType == ROCKET_TYPE_PC104)
		RingInd = !(sInB(CtlP->AiopIO[3]) & sBitMapSetTbl[ChanNum]);

	return RingInd;
}