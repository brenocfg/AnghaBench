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
typedef  int /*<<< orphan*/  u_char ;
struct IsdnCardState {int debug; scalar_t__ rcvidx; char* dlog; int /*<<< orphan*/  (* writeW6692 ) (struct IsdnCardState*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* readW6692fifo ) (struct IsdnCardState*,int /*<<< orphan*/ *,int) ;int /*<<< orphan*/ * rcvbuf; } ;

/* Variables and functions */
 int L1_DEB_ISAC ; 
 int L1_DEB_ISAC_FIFO ; 
 int L1_DEB_WARN ; 
 scalar_t__ MAX_DFRAME_LEN_L1 ; 
 int /*<<< orphan*/  QuickHex (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  W_D_CMDR ; 
 int /*<<< orphan*/  W_D_CMDR_RACK ; 
 int /*<<< orphan*/  debugl1 (struct IsdnCardState*,char*,...) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  stub1 (struct IsdnCardState*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct IsdnCardState*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub3 (struct IsdnCardState*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
W6692_empty_fifo(struct IsdnCardState *cs, int count)
{
	u_char *ptr;

	if ((cs->debug & L1_DEB_ISAC) && !(cs->debug & L1_DEB_ISAC_FIFO))
		debugl1(cs, "W6692_empty_fifo");

	if ((cs->rcvidx + count) >= MAX_DFRAME_LEN_L1) {
		if (cs->debug & L1_DEB_WARN)
			debugl1(cs, "W6692_empty_fifo overrun %d",
				cs->rcvidx + count);
		cs->writeW6692(cs, W_D_CMDR, W_D_CMDR_RACK);
		cs->rcvidx = 0;
		return;
	}
	ptr = cs->rcvbuf + cs->rcvidx;
	cs->rcvidx += count;
	cs->readW6692fifo(cs, ptr, count);
	cs->writeW6692(cs, W_D_CMDR, W_D_CMDR_RACK);
	if (cs->debug & L1_DEB_ISAC_FIFO) {
		char *t = cs->dlog;

		t += sprintf(t, "W6692_empty_fifo cnt %d", count);
		QuickHex(t, ptr, count);
		debugl1(cs, cs->dlog);
	}
}