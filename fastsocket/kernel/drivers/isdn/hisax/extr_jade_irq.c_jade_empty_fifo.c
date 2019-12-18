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
struct IsdnCardState {int debug; } ;
struct TYPE_3__ {scalar_t__ rcvidx; scalar_t__ hscx; int /*<<< orphan*/ * rcvbuf; } ;
struct TYPE_4__ {TYPE_1__ hscx; } ;
struct BCState {char* blog; TYPE_2__ hw; struct IsdnCardState* cs; } ;

/* Variables and functions */
 scalar_t__ HSCX_BUFMAX ; 
 int L1_DEB_HSCX ; 
 int L1_DEB_HSCX_FIFO ; 
 int L1_DEB_WARN ; 
 int /*<<< orphan*/  QuickHex (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  READJADEFIFO (struct IsdnCardState*,scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  WriteJADECMDR (struct IsdnCardState*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugl1 (struct IsdnCardState*,char*) ; 
 int /*<<< orphan*/  jadeRCMD_RMC ; 
 int /*<<< orphan*/  jade_HDLC_RCMD ; 
 int /*<<< orphan*/  sprintf (char*,char*,char,int) ; 

__attribute__((used)) static void
jade_empty_fifo(struct BCState *bcs, int count)
{
	u_char *ptr;
	struct IsdnCardState *cs = bcs->cs;

	if ((cs->debug & L1_DEB_HSCX) && !(cs->debug & L1_DEB_HSCX_FIFO))
		debugl1(cs, "jade_empty_fifo");

	if (bcs->hw.hscx.rcvidx + count > HSCX_BUFMAX) {
		if (cs->debug & L1_DEB_WARN)
			debugl1(cs, "jade_empty_fifo: incoming packet too large");
		WriteJADECMDR(cs, bcs->hw.hscx.hscx, jade_HDLC_RCMD, jadeRCMD_RMC);
		bcs->hw.hscx.rcvidx = 0;
		return;
	}
	ptr = bcs->hw.hscx.rcvbuf + bcs->hw.hscx.rcvidx;
	bcs->hw.hscx.rcvidx += count;
	READJADEFIFO(cs, bcs->hw.hscx.hscx, ptr, count);
	WriteJADECMDR(cs, bcs->hw.hscx.hscx, jade_HDLC_RCMD, jadeRCMD_RMC);
	if (cs->debug & L1_DEB_HSCX_FIFO) {
		char *t = bcs->blog;

		t += sprintf(t, "jade_empty_fifo %c cnt %d",
			     bcs->hw.hscx.hscx ? 'B' : 'A', count);
		QuickHex(t, ptr, count);
		debugl1(cs, bcs->blog);
	}
}