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
struct w6692_hw {int /*<<< orphan*/  name; struct w6692_ch* bc; } ;
struct TYPE_4__ {int state; scalar_t__ tx_idx; int /*<<< orphan*/  Flags; scalar_t__ tx_skb; int /*<<< orphan*/  err_xdu; int /*<<< orphan*/  nr; int /*<<< orphan*/  err_rdo; TYPE_1__* rx_skb; int /*<<< orphan*/  err_inv; int /*<<< orphan*/  err_crc; } ;
struct w6692_ch {TYPE_2__ bch; } ;
struct TYPE_3__ {scalar_t__ len; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLG_ACTIVE ; 
 int /*<<< orphan*/  FLG_HDLC ; 
 int /*<<< orphan*/  FLG_TRANSPARENT ; 
 int ReadW6692B (struct w6692_ch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  W6692_empty_Bfifo (struct w6692_ch*,int) ; 
 int /*<<< orphan*/  W_B_CMDR ; 
 int W_B_CMDR_RACK ; 
 int W_B_CMDR_RACT ; 
 int W_B_CMDR_RRST ; 
 int W_B_CMDR_XRST ; 
 int /*<<< orphan*/  W_B_EXIR ; 
 int W_B_EXI_RDOV ; 
 int W_B_EXI_RME ; 
 int W_B_EXI_RMR ; 
 int W_B_EXI_XDUN ; 
 int W_B_EXI_XFR ; 
 int W_B_FIFO_THRESH ; 
 int /*<<< orphan*/  W_B_RBCL ; 
 int /*<<< orphan*/  W_B_STAR ; 
 int W_B_STAR_CRCE ; 
 int W_B_STAR_RDOV ; 
 int W_B_STAR_RMB ; 
 int W_B_STAR_XDOW ; 
 int /*<<< orphan*/  WriteW6692B (struct w6692_ch*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  recv_Bchannel (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_next (struct w6692_ch*) ; 
 int /*<<< orphan*/  skb_trim (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
W6692B_interrupt(struct w6692_hw *card, int ch)
{
	struct w6692_ch	*wch = &card->bc[ch];
	int		count;
	u8		stat, star = 0;

	stat = ReadW6692B(wch, W_B_EXIR);
	pr_debug("%s: B%d EXIR %02x\n", card->name, wch->bch.nr, stat);
	if (stat & W_B_EXI_RME) {
		star = ReadW6692B(wch, W_B_STAR);
		if (star & (W_B_STAR_RDOV | W_B_STAR_CRCE | W_B_STAR_RMB)) {
			if ((star & W_B_STAR_RDOV) &&
			    test_bit(FLG_ACTIVE, &wch->bch.Flags)) {
				pr_debug("%s: B%d RDOV proto=%x\n", card->name,
					wch->bch.nr, wch->bch.state);
#ifdef ERROR_STATISTIC
				wch->bch.err_rdo++;
#endif
			}
			if (test_bit(FLG_HDLC, &wch->bch.Flags)) {
				if (star & W_B_STAR_CRCE) {
					pr_debug("%s: B%d CRC error\n",
						card->name, wch->bch.nr);
#ifdef ERROR_STATISTIC
					wch->bch.err_crc++;
#endif
				}
				if (star & W_B_STAR_RMB) {
					pr_debug("%s: B%d message abort\n",
						card->name, wch->bch.nr);
#ifdef ERROR_STATISTIC
					wch->bch.err_inv++;
#endif
				}
			}
			WriteW6692B(wch, W_B_CMDR, W_B_CMDR_RACK |
				W_B_CMDR_RRST | W_B_CMDR_RACT);
			if (wch->bch.rx_skb)
				skb_trim(wch->bch.rx_skb, 0);
		} else {
			count = ReadW6692B(wch, W_B_RBCL) &
				(W_B_FIFO_THRESH - 1);
			if (count == 0)
				count = W_B_FIFO_THRESH;
			W6692_empty_Bfifo(wch, count);
			recv_Bchannel(&wch->bch, 0);
		}
	}
	if (stat & W_B_EXI_RMR) {
		if (!(stat & W_B_EXI_RME))
			star = ReadW6692B(wch, W_B_STAR);
		if (star & W_B_STAR_RDOV) {
			pr_debug("%s: B%d RDOV proto=%x\n", card->name,
				wch->bch.nr, wch->bch.state);
#ifdef ERROR_STATISTIC
			wch->bch.err_rdo++;
#endif
			WriteW6692B(wch, W_B_CMDR, W_B_CMDR_RACK |
				W_B_CMDR_RRST | W_B_CMDR_RACT);
		} else {
			W6692_empty_Bfifo(wch, W_B_FIFO_THRESH);
			if (test_bit(FLG_TRANSPARENT, &wch->bch.Flags) &&
			    wch->bch.rx_skb && (wch->bch.rx_skb->len > 0))
				recv_Bchannel(&wch->bch, 0);
		}
	}
	if (stat & W_B_EXI_RDOV) {
		/* only if it is not handled yet */
		if (!(star & W_B_STAR_RDOV)) {
			pr_debug("%s: B%d RDOV IRQ proto=%x\n", card->name,
				wch->bch.nr, wch->bch.state);
#ifdef ERROR_STATISTIC
			wch->bch.err_rdo++;
#endif
			WriteW6692B(wch, W_B_CMDR, W_B_CMDR_RACK |
				W_B_CMDR_RRST | W_B_CMDR_RACT);
		}
	}
	if (stat & W_B_EXI_XFR) {
		if (!(stat & (W_B_EXI_RME | W_B_EXI_RMR))) {
			star = ReadW6692B(wch, W_B_STAR);
			pr_debug("%s: B%d star %02x\n", card->name,
				wch->bch.nr, star);
		}
		if (star & W_B_STAR_XDOW) {
			pr_debug("%s: B%d XDOW proto=%x\n", card->name,
				wch->bch.nr, wch->bch.state);
#ifdef ERROR_STATISTIC
			wch->bch.err_xdu++;
#endif
			WriteW6692B(wch, W_B_CMDR, W_B_CMDR_XRST |
				W_B_CMDR_RACT);
			/* resend */
			if (wch->bch.tx_skb) {
				if (!test_bit(FLG_TRANSPARENT, &wch->bch.Flags))
					wch->bch.tx_idx = 0;
			}
		}
		send_next(wch);
		if (stat & W_B_EXI_XDUN)
			return; /* handle XDOW only once */
	}
	if (stat & W_B_EXI_XDUN) {
		pr_debug("%s: B%d XDUN proto=%x\n", card->name,
			wch->bch.nr, wch->bch.state);
#ifdef ERROR_STATISTIC
		wch->bch.err_xdu++;
#endif
		WriteW6692B(wch, W_B_CMDR, W_B_CMDR_XRST | W_B_CMDR_RACT);
		/* resend */
		if (wch->bch.tx_skb) {
			if (!test_bit(FLG_TRANSPARENT, &wch->bch.Flags))
				wch->bch.tx_idx = 0;
		}
		send_next(wch);
	}
}