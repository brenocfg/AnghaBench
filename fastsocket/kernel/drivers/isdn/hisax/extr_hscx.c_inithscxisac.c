#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct IsdnCardState {int /*<<< orphan*/  (* writeisac ) (struct IsdnCardState*,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* BC_Write_Reg ) (struct IsdnCardState*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  HSCX_MASK ; 
 int /*<<< orphan*/  ISAC_CMDR ; 
 int /*<<< orphan*/  ISAC_MASK ; 
 int /*<<< orphan*/  clear_pending_hscx_ints (struct IsdnCardState*) ; 
 int /*<<< orphan*/  clear_pending_isac_ints (struct IsdnCardState*) ; 
 int /*<<< orphan*/  inithscx (struct IsdnCardState*) ; 
 int /*<<< orphan*/  initisac (struct IsdnCardState*) ; 
 int /*<<< orphan*/  stub1 (struct IsdnCardState*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct IsdnCardState*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct IsdnCardState*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct IsdnCardState*,int /*<<< orphan*/ ,int) ; 

void
inithscxisac(struct IsdnCardState *cs, int part)
{
	if (part & 1) {
		clear_pending_isac_ints(cs);
		clear_pending_hscx_ints(cs);
		initisac(cs);
		inithscx(cs);
	}
	if (part & 2) {
		/* Reenable all IRQ */
		cs->writeisac(cs, ISAC_MASK, 0);
		cs->BC_Write_Reg(cs, 0, HSCX_MASK, 0);
		cs->BC_Write_Reg(cs, 1, HSCX_MASK, 0);
		/* RESET Receiver and Transmitter */
		cs->writeisac(cs, ISAC_CMDR, 0x41);
	}
}