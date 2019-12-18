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
struct IsdnCardState {int /*<<< orphan*/  (* BC_Write_Reg ) (struct IsdnCardState*,int,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* writeisac ) (struct IsdnCardState*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IPACX_CMDRB ; 
 int /*<<< orphan*/  IPACX_CMDRD ; 
 int /*<<< orphan*/  IPACX_CMD_RES ; 
 int /*<<< orphan*/  IPACX_MASK ; 
 int /*<<< orphan*/  IPACX_MASKB ; 
 int /*<<< orphan*/  IPACX_MASKD ; 
 int _MASKB_IMASK ; 
 int _MASKD_IMASK ; 
 int _MASK_IMASK ; 
 int /*<<< orphan*/  bch_init (struct IsdnCardState*,int) ; 
 int /*<<< orphan*/  clear_pending_ints (struct IsdnCardState*) ; 
 int /*<<< orphan*/  dch_init (struct IsdnCardState*) ; 
 int /*<<< orphan*/  ph_command (struct IsdnCardState*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct IsdnCardState*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct IsdnCardState*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (struct IsdnCardState*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub4 (struct IsdnCardState*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub5 (struct IsdnCardState*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub6 (struct IsdnCardState*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub7 (struct IsdnCardState*,int,int /*<<< orphan*/ ,int) ; 

void
init_ipacx(struct IsdnCardState *cs, int part)
{
	if (part &1) {  // initialise chip
//##################################################  
//	printk(KERN_INFO "init_ipacx(%x)\n", part);
//##################################################  
		clear_pending_ints(cs);
		bch_init(cs, 0);
		bch_init(cs, 1);
		dch_init(cs);
	}
	if (part &2) {  // reenable all interrupts and start chip
		cs->BC_Write_Reg(cs, 0, IPACX_MASKB, _MASKB_IMASK);
		cs->BC_Write_Reg(cs, 1, IPACX_MASKB, _MASKB_IMASK);
		cs->writeisac(cs, IPACX_MASKD, _MASKD_IMASK);
		cs->writeisac(cs, IPACX_MASK, _MASK_IMASK); // global mask register

		// reset HDLC Transmitters/receivers
		cs->writeisac(cs, IPACX_CMDRD, 0x41); 
		cs->BC_Write_Reg(cs, 0, IPACX_CMDRB, 0x41);
		cs->BC_Write_Reg(cs, 1, IPACX_CMDRB, 0x41);
		ph_command(cs, IPACX_CMD_RES);
	}
}