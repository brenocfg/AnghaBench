#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  ph_state; } ;
struct TYPE_6__ {TYPE_1__ w6692; } ;
struct TYPE_7__ {long data; void* function; } ;
struct IsdnCardState {int /*<<< orphan*/  (* writeW6692 ) (struct IsdnCardState*,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* BC_Write_Reg ) (struct IsdnCardState*,int,int /*<<< orphan*/ ,int) ;TYPE_4__* bcs; TYPE_2__ dc; TYPE_3__ dbusytimer; int /*<<< orphan*/  DC_Close; int /*<<< orphan*/  setstack_d; } ;
struct TYPE_8__ {void* BC_Close; void* BC_SetStack; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_Close_W6692 ; 
 int /*<<< orphan*/  W6692Bmode (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  W6692_new_ph (struct IsdnCardState*) ; 
 int /*<<< orphan*/  W_B_EXIM ; 
 int /*<<< orphan*/  W_D_CMDR ; 
 int W_D_CMDR_RRST ; 
 int W_D_CMDR_XRST ; 
 int /*<<< orphan*/  W_D_EXIM ; 
 int /*<<< orphan*/  W_IMASK ; 
 int /*<<< orphan*/  W_L1CMD_ECK ; 
 int /*<<< orphan*/  W_L1CMD_RST ; 
 void* close_w6692state ; 
 scalar_t__ dbusy_timer_handler ; 
 int /*<<< orphan*/  init_timer (TYPE_3__*) ; 
 int /*<<< orphan*/  ph_command (struct IsdnCardState*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resetW6692 (struct IsdnCardState*) ; 
 int /*<<< orphan*/  setstack_W6692 ; 
 void* setstack_w6692 ; 
 int /*<<< orphan*/  stub1 (struct IsdnCardState*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct IsdnCardState*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (struct IsdnCardState*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub4 (struct IsdnCardState*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub5 (struct IsdnCardState*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void initW6692(struct IsdnCardState *cs, int part)
{
	if (part & 1) {
		cs->setstack_d = setstack_W6692;
		cs->DC_Close = DC_Close_W6692;
		cs->dbusytimer.function = (void *) dbusy_timer_handler;
		cs->dbusytimer.data = (long) cs;
		init_timer(&cs->dbusytimer);
		resetW6692(cs);
		ph_command(cs, W_L1CMD_RST);
		cs->dc.w6692.ph_state = W_L1CMD_RST;
		W6692_new_ph(cs);
		ph_command(cs, W_L1CMD_ECK);

		cs->bcs[0].BC_SetStack = setstack_w6692;
		cs->bcs[1].BC_SetStack = setstack_w6692;
		cs->bcs[0].BC_Close = close_w6692state;
		cs->bcs[1].BC_Close = close_w6692state;
		W6692Bmode(cs->bcs, 0, 0);
		W6692Bmode(cs->bcs + 1, 0, 0);
	}
	if (part & 2) {
		/* Reenable all IRQ */
		cs->writeW6692(cs, W_IMASK, 0x18);
		cs->writeW6692(cs, W_D_EXIM, 0x00);
		cs->BC_Write_Reg(cs, 0, W_B_EXIM, 0x00);
		cs->BC_Write_Reg(cs, 1, W_B_EXIM, 0x00);
		/* Reset D-chan receiver and transmitter */
		cs->writeW6692(cs, W_D_CMDR, W_D_CMDR_RRST | W_D_CMDR_XRST);
	}
}