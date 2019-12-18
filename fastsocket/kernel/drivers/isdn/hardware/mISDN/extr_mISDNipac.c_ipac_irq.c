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
typedef  int u8 ;
struct TYPE_4__ {int nr; int tx_idx; int /*<<< orphan*/  Flags; scalar_t__ rx_skb; } ;
struct hscx_hw {TYPE_2__ bch; TYPE_1__* ip; int /*<<< orphan*/  fifo_size; } ;
struct TYPE_3__ {int type; int /*<<< orphan*/  name; struct hscx_hw* hscx; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLG_ACTIVE ; 
 int /*<<< orphan*/  FLG_TRANSPARENT ; 
 int HSCX__EXA ; 
 int HSCX__EXB ; 
 int HSCX__ICA ; 
 int IPACX_B_RFO ; 
 int IPACX_B_RME ; 
 int IPACX_B_RPF ; 
 int IPACX_B_XDU ; 
 int IPACX_B_XPR ; 
 int /*<<< orphan*/  IPACX_ISTAB ; 
 int IPAC_B_RFO ; 
 int IPAC_B_XDU ; 
 int /*<<< orphan*/  IPAC_EXIRB ; 
 int /*<<< orphan*/  IPAC_ISTAB ; 
 int IPAC_TYPE_IPAC ; 
 int IPAC_TYPE_IPACX ; 
 int IPAC__EXA ; 
 int IPAC__EXB ; 
 int ReadHSCX (struct hscx_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hscx_cmdr (struct hscx_hw*,int) ; 
 int /*<<< orphan*/  hscx_empty_fifo (struct hscx_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hscx_fill_fifo (struct hscx_hw*) ; 
 int /*<<< orphan*/  hscx_xpr (struct hscx_hw*) ; 
 int /*<<< orphan*/  ipac_rme (struct hscx_hw*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  recv_Bchannel (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ipac_irq(struct hscx_hw *hx, u8 ista)
{
	u8 istab, m, exirb = 0;

	if (hx->ip->type & IPAC_TYPE_IPACX)
		istab = ReadHSCX(hx, IPACX_ISTAB);
	else if (hx->ip->type & IPAC_TYPE_IPAC) {
		istab = ReadHSCX(hx, IPAC_ISTAB);
		m = (hx->bch.nr & 1) ? IPAC__EXA : IPAC__EXB;
		if (m & ista) {
			exirb = ReadHSCX(hx, IPAC_EXIRB);
			pr_debug("%s: B%1d EXIRB %02x\n", hx->ip->name,
				hx->bch.nr, exirb);
		}
	} else if (hx->bch.nr & 2) { /* HSCX B */
		if (ista & (HSCX__EXA | HSCX__ICA))
			ipac_irq(&hx->ip->hscx[0], ista);
		if (ista & HSCX__EXB) {
			exirb = ReadHSCX(hx, IPAC_EXIRB);
			pr_debug("%s: B%1d EXIRB %02x\n", hx->ip->name,
				hx->bch.nr, exirb);
		}
		istab = ista & 0xF8;
	} else { /* HSCX A */
		istab = ReadHSCX(hx, IPAC_ISTAB);
		if (ista & HSCX__EXA) {
			exirb = ReadHSCX(hx, IPAC_EXIRB);
			pr_debug("%s: B%1d EXIRB %02x\n", hx->ip->name,
				hx->bch.nr, exirb);
		}
		istab = istab & 0xF8;
	}
	if (exirb & IPAC_B_XDU)
		istab |= IPACX_B_XDU;
	if (exirb & IPAC_B_RFO)
		istab |= IPACX_B_RFO;
	pr_debug("%s: B%1d ISTAB %02x\n", hx->ip->name, hx->bch.nr, istab);

	if (!test_bit(FLG_ACTIVE, &hx->bch.Flags))
		return;

	if (istab & IPACX_B_RME)
		ipac_rme(hx);

	if (istab & IPACX_B_RPF) {
		hscx_empty_fifo(hx, hx->fifo_size);
		if (test_bit(FLG_TRANSPARENT, &hx->bch.Flags)) {
			/* receive transparent audio data */
			if (hx->bch.rx_skb)
				recv_Bchannel(&hx->bch, 0);
		}
	}

	if (istab & IPACX_B_RFO) {
		pr_debug("%s: B%1d RFO error\n", hx->ip->name, hx->bch.nr);
		hscx_cmdr(hx, 0x40);	/* RRES */
	}

	if (istab & IPACX_B_XPR)
		hscx_xpr(hx);

	if (istab & IPACX_B_XDU) {
		if (test_bit(FLG_TRANSPARENT, &hx->bch.Flags)) {
			hscx_fill_fifo(hx);
			return;
		}
		pr_debug("%s: B%1d XDU error at len %d\n", hx->ip->name,
			hx->bch.nr, hx->bch.tx_idx);
		hx->bch.tx_idx = 0;
		hscx_cmdr(hx, 0x01);	/* XRES */
	}
}