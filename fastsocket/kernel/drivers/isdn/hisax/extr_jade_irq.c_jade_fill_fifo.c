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
struct IsdnCardState {int debug; } ;
struct TYPE_4__ {int count; scalar_t__ hscx; } ;
struct TYPE_5__ {TYPE_1__ hscx; } ;
struct BCState {scalar_t__ mode; int tx_cnt; char* blog; TYPE_2__ hw; TYPE_3__* tx_skb; struct IsdnCardState* cs; } ;
struct TYPE_6__ {int len; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int L1_DEB_HSCX ; 
 int L1_DEB_HSCX_FIFO ; 
 scalar_t__ L1_MODE_TRANS ; 
 int /*<<< orphan*/  QuickHex (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  WRITEJADEFIFO (struct IsdnCardState*,scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  WriteJADECMDR (struct IsdnCardState*,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  debugl1 (struct IsdnCardState*,char*) ; 
 int jadeXCMD_XF ; 
 int jadeXCMD_XME ; 
 int /*<<< orphan*/  jade_HDLC_XCMD ; 
 int /*<<< orphan*/  skb_pull (TYPE_3__*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char,int) ; 
 int /*<<< orphan*/  waitforXFW (struct IsdnCardState*,scalar_t__) ; 

__attribute__((used)) static void
jade_fill_fifo(struct BCState *bcs)
{
	struct IsdnCardState *cs = bcs->cs;
	int more, count;
	int fifo_size = 32;
	u_char *ptr;

	if ((cs->debug & L1_DEB_HSCX) && !(cs->debug & L1_DEB_HSCX_FIFO))
		debugl1(cs, "jade_fill_fifo");

	if (!bcs->tx_skb)
		return;
	if (bcs->tx_skb->len <= 0)
		return;

	more = (bcs->mode == L1_MODE_TRANS) ? 1 : 0;
	if (bcs->tx_skb->len > fifo_size) {
		more = !0;
		count = fifo_size;
	} else
		count = bcs->tx_skb->len;

	waitforXFW(cs, bcs->hw.hscx.hscx);
	ptr = bcs->tx_skb->data;
	skb_pull(bcs->tx_skb, count);
	bcs->tx_cnt -= count;
	bcs->hw.hscx.count += count;
	WRITEJADEFIFO(cs, bcs->hw.hscx.hscx, ptr, count);
	WriteJADECMDR(cs, bcs->hw.hscx.hscx, jade_HDLC_XCMD, more ? jadeXCMD_XF : (jadeXCMD_XF|jadeXCMD_XME));
	if (cs->debug & L1_DEB_HSCX_FIFO) {
		char *t = bcs->blog;

		t += sprintf(t, "jade_fill_fifo %c cnt %d",
			     bcs->hw.hscx.hscx ? 'B' : 'A', count);
		QuickHex(t, ptr, count);
		debugl1(cs, bcs->blog);
	}
}