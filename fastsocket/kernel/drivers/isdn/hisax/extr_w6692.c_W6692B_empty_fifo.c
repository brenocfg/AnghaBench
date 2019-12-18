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
typedef  int /*<<< orphan*/  u_char ;
struct IsdnCardState {int debug; int /*<<< orphan*/  (* BC_Write_Reg ) (struct IsdnCardState*,int,int /*<<< orphan*/ ,int) ;} ;
struct TYPE_3__ {scalar_t__ rcvidx; int /*<<< orphan*/ * rcvbuf; } ;
struct TYPE_4__ {TYPE_1__ w6692; } ;
struct BCState {int channel; char* blog; TYPE_2__ hw; struct IsdnCardState* cs; } ;

/* Variables and functions */
 scalar_t__ HSCX_BUFMAX ; 
 int L1_DEB_HSCX ; 
 int L1_DEB_HSCX_FIFO ; 
 int L1_DEB_WARN ; 
 int /*<<< orphan*/  QuickHex (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  READW6692BFIFO (struct IsdnCardState*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  W_B_CMDR ; 
 int W_B_CMDR_RACK ; 
 int W_B_CMDR_RACT ; 
 int /*<<< orphan*/  debugl1 (struct IsdnCardState*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int) ; 
 int /*<<< orphan*/  stub1 (struct IsdnCardState*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct IsdnCardState*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
W6692B_empty_fifo(struct BCState *bcs, int count)
{
	u_char *ptr;
	struct IsdnCardState *cs = bcs->cs;

	if ((cs->debug & L1_DEB_HSCX) && !(cs->debug & L1_DEB_HSCX_FIFO))
		debugl1(cs, "W6692B_empty_fifo");

	if (bcs->hw.w6692.rcvidx + count > HSCX_BUFMAX) {
		if (cs->debug & L1_DEB_WARN)
			debugl1(cs, "W6692B_empty_fifo: incoming packet too large");
		cs->BC_Write_Reg(cs, bcs->channel, W_B_CMDR, W_B_CMDR_RACK | W_B_CMDR_RACT);
		bcs->hw.w6692.rcvidx = 0;
		return;
	}
	ptr = bcs->hw.w6692.rcvbuf + bcs->hw.w6692.rcvidx;
	bcs->hw.w6692.rcvidx += count;
	READW6692BFIFO(cs, bcs->channel, ptr, count);
	cs->BC_Write_Reg(cs, bcs->channel, W_B_CMDR, W_B_CMDR_RACK | W_B_CMDR_RACT);
	if (cs->debug & L1_DEB_HSCX_FIFO) {
		char *t = bcs->blog;

		t += sprintf(t, "W6692B_empty_fifo %c cnt %d",
			     bcs->channel + '1', count);
		QuickHex(t, ptr, count);
		debugl1(cs, bcs->blog);
	}
}