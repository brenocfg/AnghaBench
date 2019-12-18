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
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_5__ {int* mon_tx; int arcofi_bc; int mocr; scalar_t__ mon_txp; int /*<<< orphan*/  mon_txc; TYPE_1__* arcofi_list; } ;
struct TYPE_6__ {TYPE_2__ isac; } ;
struct IsdnCardState {TYPE_3__ dc; int /*<<< orphan*/  (* writeisac ) (struct IsdnCardState*,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* readisac ) (struct IsdnCardState*,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  msg; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISAC_MOCR ; 
 int /*<<< orphan*/  ISAC_MOSR ; 
 int /*<<< orphan*/  ISAC_MOX1 ; 
 int /*<<< orphan*/  add_arcofi_timer (struct IsdnCardState*) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct IsdnCardState*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct IsdnCardState*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct IsdnCardState*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub4 (struct IsdnCardState*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
send_arcofi(struct IsdnCardState *cs) {
	u_char val;
	
	add_arcofi_timer(cs);
	cs->dc.isac.mon_txp = 0;
	cs->dc.isac.mon_txc = cs->dc.isac.arcofi_list->len;
	memcpy(cs->dc.isac.mon_tx, cs->dc.isac.arcofi_list->msg, cs->dc.isac.mon_txc);
	switch(cs->dc.isac.arcofi_bc) {
		case 0: break;
		case 1: cs->dc.isac.mon_tx[1] |= 0x40;
			break;
		default: break;
	}
	cs->dc.isac.mocr &= 0x0f;
	cs->dc.isac.mocr |= 0xa0;
	cs->writeisac(cs, ISAC_MOCR, cs->dc.isac.mocr);
	val = cs->readisac(cs, ISAC_MOSR);
	cs->writeisac(cs, ISAC_MOX1, cs->dc.isac.mon_tx[cs->dc.isac.mon_txp++]);
	cs->dc.isac.mocr |= 0x10;
	cs->writeisac(cs, ISAC_MOCR, cs->dc.isac.mocr);
}