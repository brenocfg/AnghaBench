#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct IsdnCardState {TYPE_3__* bcs; int /*<<< orphan*/  (* BC_Write_Reg ) (struct IsdnCardState*,int,int /*<<< orphan*/ ,int) ;} ;
struct TYPE_4__ {int hscx; } ;
struct TYPE_5__ {TYPE_1__ hscx; } ;
struct TYPE_6__ {TYPE_2__ hw; void* BC_Close; void* BC_SetStack; } ;

/* Variables and functions */
 void* close_jadestate ; 
 int jadeINDIRECT_HAH1 ; 
 int jadeINDIRECT_HAH2 ; 
 int jadeINT_HDLC1 ; 
 int jadeINT_HDLC2 ; 
 int jadeMODE_TMO ; 
 int jade_HDLCCNTRACCESS ; 
 int /*<<< orphan*/  jade_HDLC_CCR0 ; 
 int /*<<< orphan*/  jade_HDLC_IMR ; 
 int /*<<< orphan*/  jade_HDLC_MODE ; 
 int /*<<< orphan*/  jade_INT ; 
 int /*<<< orphan*/  jade_write_indirect (struct IsdnCardState*,int,int) ; 
 int /*<<< orphan*/  modejade (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* setstack_jade ; 
 int /*<<< orphan*/  stub1 (struct IsdnCardState*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct IsdnCardState*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (struct IsdnCardState*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub4 (struct IsdnCardState*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub5 (struct IsdnCardState*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub6 (struct IsdnCardState*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub7 (struct IsdnCardState*,int,int /*<<< orphan*/ ,int) ; 

void
initjade(struct IsdnCardState *cs)
{
	cs->bcs[0].BC_SetStack = setstack_jade;
	cs->bcs[1].BC_SetStack = setstack_jade;
	cs->bcs[0].BC_Close = close_jadestate;
	cs->bcs[1].BC_Close = close_jadestate;
	cs->bcs[0].hw.hscx.hscx = 0;
	cs->bcs[1].hw.hscx.hscx = 1;

	/* Stop DSP audio tx/rx */
	jade_write_indirect(cs, 0x11, 0x0f);
	jade_write_indirect(cs, 0x17, 0x2f);

	/* Transparent Mode, RxTx inactive, No Test, No RFS/TFS */
	cs->BC_Write_Reg(cs, 0, jade_HDLC_MODE, jadeMODE_TMO);
	cs->BC_Write_Reg(cs, 1, jade_HDLC_MODE, jadeMODE_TMO);
	/* Power down, 1-Idle, RxTx least significant bit first */
	cs->BC_Write_Reg(cs, 0, jade_HDLC_CCR0, 0x00);
	cs->BC_Write_Reg(cs, 1, jade_HDLC_CCR0, 0x00);
	/* Mask all interrupts */
	cs->BC_Write_Reg(cs, 0, jade_HDLC_IMR,  0x00);
	cs->BC_Write_Reg(cs, 1, jade_HDLC_IMR,  0x00);
	/* Setup host access to hdlc controller */
	jade_write_indirect(cs, jade_HDLCCNTRACCESS, (jadeINDIRECT_HAH1|jadeINDIRECT_HAH2));
	/* Unmask HDLC int (don't forget DSP int later on)*/
	cs->BC_Write_Reg(cs, -1,jade_INT, (jadeINT_HDLC1|jadeINT_HDLC2));

	/* once again TRANSPARENT */	
	modejade(cs->bcs, 0, 0);
	modejade(cs->bcs + 1, 0, 0);
}