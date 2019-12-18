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
struct TYPE_3__ {int mocr; int adf2; int /*<<< orphan*/ * mon_rx; int /*<<< orphan*/ * mon_tx; } ;
struct TYPE_4__ {TYPE_1__ icc; } ;
struct IsdnCardState {int /*<<< orphan*/  (* writeisac ) (struct IsdnCardState*,int /*<<< orphan*/ ,int) ;TYPE_2__ dc; int /*<<< orphan*/  HW_Flags; int /*<<< orphan*/  DC_Close; int /*<<< orphan*/  setstack_d; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_Close_icc ; 
 int /*<<< orphan*/  HW_IOM1 ; 
 int /*<<< orphan*/  ICC_ADF1 ; 
 int /*<<< orphan*/  ICC_ADF2 ; 
 int /*<<< orphan*/  ICC_CMD_DI ; 
 int /*<<< orphan*/  ICC_CMD_RES ; 
 int /*<<< orphan*/  ICC_MASK ; 
 int /*<<< orphan*/  ICC_MODE ; 
 int /*<<< orphan*/  ICC_SPCR ; 
 int /*<<< orphan*/  ICC_SQXR ; 
 int /*<<< orphan*/  ICC_STCR ; 
 int /*<<< orphan*/  ICC_TIMR ; 
 int /*<<< orphan*/  ph_command (struct IsdnCardState*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setstack_icc ; 
 int /*<<< orphan*/  stub1 (struct IsdnCardState*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub10 (struct IsdnCardState*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub11 (struct IsdnCardState*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub12 (struct IsdnCardState*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub13 (struct IsdnCardState*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub14 (struct IsdnCardState*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct IsdnCardState*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (struct IsdnCardState*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub4 (struct IsdnCardState*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub5 (struct IsdnCardState*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub6 (struct IsdnCardState*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub7 (struct IsdnCardState*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub8 (struct IsdnCardState*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub9 (struct IsdnCardState*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
initicc(struct IsdnCardState *cs)
{
	cs->setstack_d = setstack_icc;
	cs->DC_Close = DC_Close_icc;
	cs->dc.icc.mon_tx = NULL;
	cs->dc.icc.mon_rx = NULL;
  	cs->writeisac(cs, ICC_MASK, 0xff);
  	cs->dc.icc.mocr = 0xaa;
	if (test_bit(HW_IOM1, &cs->HW_Flags)) {
		/* IOM 1 Mode */
		cs->writeisac(cs, ICC_ADF2, 0x0);
		cs->writeisac(cs, ICC_SPCR, 0xa);
		cs->writeisac(cs, ICC_ADF1, 0x2);
		cs->writeisac(cs, ICC_STCR, 0x70);
		cs->writeisac(cs, ICC_MODE, 0xc9);
	} else {
		/* IOM 2 Mode */
		if (!cs->dc.icc.adf2)
			cs->dc.icc.adf2 = 0x80;
		cs->writeisac(cs, ICC_ADF2, cs->dc.icc.adf2);
		cs->writeisac(cs, ICC_SQXR, 0xa0);
		cs->writeisac(cs, ICC_SPCR, 0x20);
		cs->writeisac(cs, ICC_STCR, 0x70);
		cs->writeisac(cs, ICC_MODE, 0xca);
		cs->writeisac(cs, ICC_TIMR, 0x00);
		cs->writeisac(cs, ICC_ADF1, 0x20);
	}
	ph_command(cs, ICC_CMD_RES);
	cs->writeisac(cs, ICC_MASK, 0x0);
	ph_command(cs, ICC_CMD_DI);
}