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
struct IsdnCardState {int (* BC_Read_Reg ) (struct IsdnCardState*,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* BC_Write_Reg ) (struct IsdnCardState*,int,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  debugl1 (struct IsdnCardState*,char*) ; 
 int /*<<< orphan*/  jade_HDLC_IMR ; 
 int /*<<< orphan*/  jade_HDLC_ISR ; 
 int /*<<< orphan*/  jade_HDLC_STAR ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  stub1 (struct IsdnCardState*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct IsdnCardState*,int,int /*<<< orphan*/ ,int) ; 
 int stub3 (struct IsdnCardState*,int,int /*<<< orphan*/ ) ; 
 int stub4 (struct IsdnCardState*,int,int /*<<< orphan*/ ) ; 
 int stub5 (struct IsdnCardState*,int,int /*<<< orphan*/ ) ; 
 int stub6 (struct IsdnCardState*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (struct IsdnCardState*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub8 (struct IsdnCardState*,int,int /*<<< orphan*/ ,int) ; 

void
clear_pending_jade_ints(struct IsdnCardState *cs)
{
	int val;
	char tmp[64];

	cs->BC_Write_Reg(cs, 0, jade_HDLC_IMR, 0x00);
	cs->BC_Write_Reg(cs, 1, jade_HDLC_IMR, 0x00);

	val = cs->BC_Read_Reg(cs, 1, jade_HDLC_ISR);
	sprintf(tmp, "jade B ISTA %x", val);
	debugl1(cs, tmp);
	val = cs->BC_Read_Reg(cs, 0, jade_HDLC_ISR);
	sprintf(tmp, "jade A ISTA %x", val);
	debugl1(cs, tmp);
	val = cs->BC_Read_Reg(cs, 1, jade_HDLC_STAR);
	sprintf(tmp, "jade B STAR %x", val);
	debugl1(cs, tmp);
	val = cs->BC_Read_Reg(cs, 0, jade_HDLC_STAR);
	sprintf(tmp, "jade A STAR %x", val);
	debugl1(cs, tmp);
	/* Unmask ints */
	cs->BC_Write_Reg(cs, 0, jade_HDLC_IMR, 0xF8);
	cs->BC_Write_Reg(cs, 1, jade_HDLC_IMR, 0xF8);
}