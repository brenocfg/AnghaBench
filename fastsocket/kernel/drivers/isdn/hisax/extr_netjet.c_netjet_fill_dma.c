#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
struct TYPE_8__ {int free; int /*<<< orphan*/ * send; int /*<<< orphan*/ * s_end; int /*<<< orphan*/ * sendp; } ;
struct TYPE_9__ {TYPE_3__ tiger; } ;
struct BCState {scalar_t__ mode; int /*<<< orphan*/  Flag; int /*<<< orphan*/  channel; TYPE_5__* cs; TYPE_4__ hw; int /*<<< orphan*/  tx_skb; } ;
struct TYPE_6__ {scalar_t__ base; } ;
struct TYPE_7__ {TYPE_1__ njet; } ;
struct TYPE_10__ {int debug; TYPE_2__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  BC_FLG_BUSY ; 
 int /*<<< orphan*/  BC_FLG_EMPTY ; 
 int /*<<< orphan*/  BC_FLG_HALF ; 
 int /*<<< orphan*/  BC_FLG_NOFRAME ; 
 int L1_DEB_HSCX ; 
 scalar_t__ L1_MODE_HDLC ; 
 scalar_t__ NETJET_DMA_READ_ADR ; 
 int NETJET_DMA_TXSIZE ; 
 int /*<<< orphan*/ * bus_to_virt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugl1 (TYPE_5__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inl (scalar_t__) ; 
 scalar_t__ make_raw_data (struct BCState*) ; 
 scalar_t__ make_raw_data_56k (struct BCState*) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_raw (struct BCState*,int /*<<< orphan*/ *,int) ; 

void netjet_fill_dma(struct BCState *bcs)
{
	register u_int *p, *sp;
	register int cnt;

	if (!bcs->tx_skb)
		return;
	if (bcs->cs->debug & L1_DEB_HSCX)
		debugl1(bcs->cs,"tiger fill_dma1: c%d %4x", bcs->channel,
			bcs->Flag);
	if (test_and_set_bit(BC_FLG_BUSY, &bcs->Flag))
		return;
	if (bcs->mode == L1_MODE_HDLC) { // it's 64k
		if (make_raw_data(bcs))
			return;		
	}
	else { // it's 56k
		if (make_raw_data_56k(bcs))
			return;		
	};
	if (bcs->cs->debug & L1_DEB_HSCX)
		debugl1(bcs->cs,"tiger fill_dma2: c%d %4x", bcs->channel,
			bcs->Flag);
	if (test_and_clear_bit(BC_FLG_NOFRAME, &bcs->Flag)) {
		write_raw(bcs, bcs->hw.tiger.sendp, bcs->hw.tiger.free);
	} else if (test_and_clear_bit(BC_FLG_HALF, &bcs->Flag)) {
		p = bus_to_virt(inl(bcs->cs->hw.njet.base + NETJET_DMA_READ_ADR));
		sp = bcs->hw.tiger.sendp;
		if (p == bcs->hw.tiger.s_end)
			p = bcs->hw.tiger.send -1;
		if (sp == bcs->hw.tiger.s_end)
			sp = bcs->hw.tiger.send -1;
		cnt = p - sp;
		if (cnt <0) {
			write_raw(bcs, bcs->hw.tiger.sendp, bcs->hw.tiger.free);
		} else {
			p++;
			cnt++;
			if (p > bcs->hw.tiger.s_end)
				p = bcs->hw.tiger.send;
			p++;
			cnt++;
			if (p > bcs->hw.tiger.s_end)
				p = bcs->hw.tiger.send;
			write_raw(bcs, p, bcs->hw.tiger.free - cnt);
		}
	} else if (test_and_clear_bit(BC_FLG_EMPTY, &bcs->Flag)) {
		p = bus_to_virt(inl(bcs->cs->hw.njet.base + NETJET_DMA_READ_ADR));
		cnt = bcs->hw.tiger.s_end - p;
		if (cnt < 2) {
			p = bcs->hw.tiger.send + 1;
			cnt = NETJET_DMA_TXSIZE/2 - 2;
		} else {
			p++;
			p++;
			if (cnt <= (NETJET_DMA_TXSIZE/2))
				cnt += NETJET_DMA_TXSIZE/2;
			cnt--;
			cnt--;
		}
		write_raw(bcs, p, cnt);
	}
	if (bcs->cs->debug & L1_DEB_HSCX)
		debugl1(bcs->cs,"tiger fill_dma3: c%d %4x", bcs->channel,
			bcs->Flag);
}