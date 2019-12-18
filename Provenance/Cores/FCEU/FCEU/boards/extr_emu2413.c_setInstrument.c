#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8 ;
typedef  size_t uint32 ;
typedef  int /*<<< orphan*/  src ;
struct TYPE_8__ {int AM; int PM; int EG; int KR; int ML; int KL; int TL; int WF; int AR; int DR; int SL; int RR; int /*<<< orphan*/ * FB; } ;
struct TYPE_11__ {TYPE_1__ patch; } ;
struct TYPE_10__ {TYPE_1__ patch; } ;
struct TYPE_9__ {size_t* patch_number; int* CustInst; } ;
typedef  TYPE_1__ OPLL_PATCH ;
typedef  TYPE_2__ OPLL ;

/* Variables and functions */
 TYPE_6__* CAR (TYPE_2__*,size_t) ; 
 TYPE_4__* MOD (TYPE_2__*,size_t) ; 
 int** default_inst ; 

__attribute__((used)) static void setInstrument(OPLL * opll, uint32 i, uint32 inst) {
	const uint8 *src;
	OPLL_PATCH *modp, *carp;

	opll->patch_number[i] = inst;

	if (inst)
		src = default_inst[inst - 1];
	else
		src = opll->CustInst;

	modp = &MOD(opll, i)->patch;
	carp = &CAR(opll, i)->patch;

	modp->AM = (src[0] >> 7) & 1;
	modp->PM = (src[0] >> 6) & 1;
	modp->EG = (src[0] >> 5) & 1;
	modp->KR = (src[0] >> 4) & 1;
	modp->ML = (src[0] & 0xF);

	carp->AM = (src[1] >> 7) & 1;
	carp->PM = (src[1] >> 6) & 1;
	carp->EG = (src[1] >> 5) & 1;
	carp->KR = (src[1] >> 4) & 1;
	carp->ML = (src[1] & 0xF);

	modp->KL = (src[2] >> 6) & 3;
	modp->TL = (src[2] & 0x3F);

	carp->KL = (src[3] >> 6) & 3;
	carp->WF = (src[3] >> 4) & 1;

	modp->WF = (src[3] >> 3) & 1;

	modp->FB = (src[3]) & 7;

	modp->AR = (src[4] >> 4) & 0xF;
	modp->DR = (src[4] & 0xF);

	carp->AR = (src[5] >> 4) & 0xF;
	carp->DR = (src[5] & 0xF);

	modp->SL = (src[6] >> 4) & 0xF;
	modp->RR = (src[6] & 0xF);

	carp->SL = (src[7] >> 4) & 0xF;
	carp->RR = (src[7] & 0xF);
}