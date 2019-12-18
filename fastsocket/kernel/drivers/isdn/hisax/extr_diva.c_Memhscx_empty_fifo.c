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
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_5__ {int /*<<< orphan*/  cfg_reg; } ;
struct TYPE_6__ {TYPE_1__ diva; } ;
struct IsdnCardState {int debug; TYPE_2__ hw; } ;
struct TYPE_7__ {scalar_t__ rcvidx; scalar_t__ hscx; int /*<<< orphan*/ * rcvbuf; } ;
struct TYPE_8__ {TYPE_3__ hscx; } ;
struct BCState {char* blog; TYPE_4__ hw; struct IsdnCardState* cs; } ;

/* Variables and functions */
 scalar_t__ HSCX_BUFMAX ; 
 int L1_DEB_HSCX ; 
 int L1_DEB_HSCX_FIFO ; 
 int L1_DEB_WARN ; 
 int /*<<< orphan*/  MemWriteHSCXCMDR (struct IsdnCardState*,scalar_t__,int) ; 
 int /*<<< orphan*/  QuickHex (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  debugl1 (struct IsdnCardState*,char*) ; 
 int /*<<< orphan*/  memreadreg (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char,int) ; 

__attribute__((used)) static void
Memhscx_empty_fifo(struct BCState *bcs, int count)
{
	u_char *ptr;
	struct IsdnCardState *cs = bcs->cs;
	int cnt;

	if ((cs->debug & L1_DEB_HSCX) && !(cs->debug & L1_DEB_HSCX_FIFO))
		debugl1(cs, "hscx_empty_fifo");

	if (bcs->hw.hscx.rcvidx + count > HSCX_BUFMAX) {
		if (cs->debug & L1_DEB_WARN)
			debugl1(cs, "hscx_empty_fifo: incoming packet too large");
		MemWriteHSCXCMDR(cs, bcs->hw.hscx.hscx, 0x80);
		bcs->hw.hscx.rcvidx = 0;
		return;
	}
	ptr = bcs->hw.hscx.rcvbuf + bcs->hw.hscx.rcvidx;
	cnt = count;
	while (cnt--)
		*ptr++ = memreadreg(cs->hw.diva.cfg_reg, bcs->hw.hscx.hscx ? 0x40 : 0);
	MemWriteHSCXCMDR(cs, bcs->hw.hscx.hscx, 0x80);
	ptr = bcs->hw.hscx.rcvbuf + bcs->hw.hscx.rcvidx;
	bcs->hw.hscx.rcvidx += count;
	if (cs->debug & L1_DEB_HSCX_FIFO) {
		char *t = bcs->blog;

		t += sprintf(t, "hscx_empty_fifo %c cnt %d",
			     bcs->hw.hscx.hscx ? 'B' : 'A', count);
		QuickHex(t, ptr, count);
		debugl1(cs, bcs->blog);
	}
}