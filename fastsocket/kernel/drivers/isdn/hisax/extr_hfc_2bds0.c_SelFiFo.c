#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
struct TYPE_3__ {int fifo; } ;
struct TYPE_4__ {TYPE_1__ hfcD; } ;
struct IsdnCardState {int /*<<< orphan*/  (* BC_Write_Reg ) (struct IsdnCardState*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;TYPE_2__ hw; } ;

/* Variables and functions */
 int HFCB_B1 ; 
 int HFCB_B2 ; 
 int HFCB_FIFO ; 
 int HFCB_REC ; 
 int HFCB_SEND ; 
 int HFCB_Z1 ; 
 int /*<<< orphan*/  HFCD_DATA ; 
 int HFCD_FIFO ; 
 int HFCD_REC ; 
 int HFCD_SEND ; 
 int HFCD_Z1 ; 
 int /*<<< orphan*/  WaitForBusy (struct IsdnCardState*) ; 
 int /*<<< orphan*/  WaitNoBusy (struct IsdnCardState*) ; 
 int /*<<< orphan*/  debugl1 (struct IsdnCardState*,char*) ; 
 int /*<<< orphan*/  stub1 (struct IsdnCardState*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
SelFiFo(struct IsdnCardState *cs, u_char FiFo)
{
	u_char cip;

	if (cs->hw.hfcD.fifo == FiFo)
		return(1);
	switch(FiFo) {
		case 0: cip = HFCB_FIFO | HFCB_Z1 | HFCB_SEND | HFCB_B1;
			break;
		case 1: cip = HFCB_FIFO | HFCB_Z1 | HFCB_REC | HFCB_B1;
			break;
		case 2: cip = HFCB_FIFO | HFCB_Z1 | HFCB_SEND | HFCB_B2;
			break;
		case 3: cip = HFCB_FIFO | HFCB_Z1 | HFCB_REC | HFCB_B2;
			break;
		case 4: cip = HFCD_FIFO | HFCD_Z1 | HFCD_SEND;
			break;
		case 5: cip = HFCD_FIFO | HFCD_Z1 | HFCD_REC;
			break;
		default:
			debugl1(cs, "SelFiFo Error");
			return(0);
	}
	cs->hw.hfcD.fifo = FiFo;
	WaitNoBusy(cs);
	cs->BC_Write_Reg(cs, HFCD_DATA, cip, 0);
	WaitForBusy(cs);
	return(2);
}