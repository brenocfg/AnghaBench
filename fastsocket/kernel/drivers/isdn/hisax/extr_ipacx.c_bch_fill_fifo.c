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
typedef  int u_char ;
struct IsdnCardState {int debug; int /*<<< orphan*/  (* BC_Write_Reg ) (struct IsdnCardState*,int,int /*<<< orphan*/ ,int) ;} ;
struct TYPE_4__ {int hscx; int count; } ;
struct TYPE_5__ {TYPE_1__ hscx; } ;
struct BCState {scalar_t__ mode; int tx_cnt; char* blog; TYPE_2__ hw; TYPE_3__* tx_skb; struct IsdnCardState* cs; } ;
struct TYPE_6__ {int len; int* data; } ;

/* Variables and functions */
 int B_FIFO_SIZE ; 
 int /*<<< orphan*/  IPACX_CMDRB ; 
 int /*<<< orphan*/  IPACX_XFIFOB ; 
 int L1_DEB_HSCX ; 
 int L1_DEB_HSCX_FIFO ; 
 scalar_t__ L1_MODE_TRANS ; 
 int /*<<< orphan*/  QuickHex (char*,int*,int) ; 
 int /*<<< orphan*/  debugl1 (struct IsdnCardState*,char*) ; 
 int /*<<< orphan*/  skb_pull (TYPE_3__*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int) ; 
 int /*<<< orphan*/  stub1 (struct IsdnCardState*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct IsdnCardState*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bch_fill_fifo(struct BCState *bcs)
{
	struct IsdnCardState *cs;
	int more, count, cnt;
	u_char *ptr, *p, hscx;

	cs = bcs->cs;
	if ((cs->debug &L1_DEB_HSCX) && !(cs->debug &L1_DEB_HSCX_FIFO))
		debugl1(cs, "bch_fill_fifo()");

	if (!bcs->tx_skb)           return;
	if (bcs->tx_skb->len <= 0)  return;

	hscx = bcs->hw.hscx.hscx;
	more = (bcs->mode == L1_MODE_TRANS) ? 1 : 0;
	if (bcs->tx_skb->len > B_FIFO_SIZE) {
		more  = 1;
		count = B_FIFO_SIZE;
	} else {
		count = bcs->tx_skb->len;
	}  
	cnt = count;
    
	p = ptr = bcs->tx_skb->data;
	skb_pull(bcs->tx_skb, count);
	bcs->tx_cnt -= count;
	bcs->hw.hscx.count += count;
	while (cnt--) cs->BC_Write_Reg(cs, hscx, IPACX_XFIFOB, *p++); 
	cs->BC_Write_Reg(cs, hscx, IPACX_CMDRB, (more ? 0x08 : 0x0a));
  
	if (cs->debug &L1_DEB_HSCX_FIFO) {
		char *t = bcs->blog;

		t += sprintf(t, "chb_fill_fifo() B-%d cnt %d", hscx, count);
		QuickHex(t, ptr, count);
		debugl1(cs, bcs->blog);
	}
}