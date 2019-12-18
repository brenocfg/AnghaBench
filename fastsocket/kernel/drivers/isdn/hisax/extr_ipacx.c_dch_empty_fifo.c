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
struct IsdnCardState {int debug; scalar_t__ rcvidx; char* dlog; int /*<<< orphan*/  (* writeisac ) (struct IsdnCardState*,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* readisacfifo ) (struct IsdnCardState*,int /*<<< orphan*/ *,int) ;int /*<<< orphan*/ * rcvbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPACX_CMDRD ; 
 int L1_DEB_ISAC ; 
 int L1_DEB_ISAC_FIFO ; 
 int L1_DEB_WARN ; 
 scalar_t__ MAX_DFRAME_LEN_L1 ; 
 int /*<<< orphan*/  QuickHex (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  debugl1 (struct IsdnCardState*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  stub1 (struct IsdnCardState*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct IsdnCardState*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub3 (struct IsdnCardState*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void 
dch_empty_fifo(struct IsdnCardState *cs, int count)
{
	u_char *ptr;

	if ((cs->debug &L1_DEB_ISAC) && !(cs->debug &L1_DEB_ISAC_FIFO))
		debugl1(cs, "dch_empty_fifo()");

  // message too large, remove
	if ((cs->rcvidx + count) >= MAX_DFRAME_LEN_L1) {
		if (cs->debug &L1_DEB_WARN)
			debugl1(cs, "dch_empty_fifo() incoming message too large");
	  cs->writeisac(cs, IPACX_CMDRD, 0x80); // RMC
		cs->rcvidx = 0;
		return;
	}
  
	ptr = cs->rcvbuf + cs->rcvidx;
	cs->rcvidx += count;
  
	cs->readisacfifo(cs, ptr, count);
	cs->writeisac(cs, IPACX_CMDRD, 0x80); // RMC
  
	if (cs->debug &L1_DEB_ISAC_FIFO) {
		char *t = cs->dlog;

		t += sprintf(t, "dch_empty_fifo() cnt %d", count);
		QuickHex(t, ptr, count);
		debugl1(cs, cs->dlog);
	}
}