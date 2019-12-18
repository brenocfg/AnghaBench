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
typedef  int u32 ;
struct TYPE_5__ {int /*<<< orphan*/  cmd; scalar_t__ xml; } ;
struct TYPE_6__ {TYPE_2__ sr; } ;
struct hdlc_hw {TYPE_3__ ctrl; } ;
struct fritzcard {int /*<<< orphan*/  name; struct hdlc_hw* hdlc; } ;
struct bchannel {int nr; int Flags; scalar_t__ tx_idx; TYPE_1__* tx_skb; scalar_t__ rx_skb; struct fritzcard* hw; } ;
struct TYPE_4__ {scalar_t__ len; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLG_TRANSPARENT ; 
 int /*<<< orphan*/  HDLC_CMD_RRS ; 
 int /*<<< orphan*/  HDLC_CMD_XRS ; 
 int HDLC_INT_RPR ; 
 int HDLC_INT_XDU ; 
 int HDLC_INT_XPR ; 
 int HDLC_STAT_CRCVFR ; 
 int HDLC_STAT_CRCVFRRAB ; 
 int HDLC_STAT_RDO ; 
 int HDLC_STAT_RME ; 
 int HDLC_STAT_RML_MASK ; 
 int /*<<< orphan*/  HDLC_irq_xpr (struct bchannel*) ; 
 int /*<<< orphan*/  hdlc_empty_fifo (struct bchannel*,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  recv_Bchannel (struct bchannel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_trim (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  write_ctrl (struct bchannel*,int) ; 

__attribute__((used)) static void
HDLC_irq(struct bchannel *bch, u32 stat)
{
	struct fritzcard *fc = bch->hw;
	int		len;
	struct hdlc_hw	*hdlc;

	hdlc = &fc->hdlc[(bch->nr - 1) & 1];
	pr_debug("%s: ch%d stat %#x\n", fc->name, bch->nr, stat);
	if (stat & HDLC_INT_RPR) {
		if (stat & HDLC_STAT_RDO) {
			hdlc->ctrl.sr.xml = 0;
			hdlc->ctrl.sr.cmd |= HDLC_CMD_RRS;
			write_ctrl(bch, 1);
			hdlc->ctrl.sr.cmd &= ~HDLC_CMD_RRS;
			write_ctrl(bch, 1);
			if (bch->rx_skb)
				skb_trim(bch->rx_skb, 0);
		} else {
			len = (stat & HDLC_STAT_RML_MASK) >> 8;
			if (!len)
				len = 32;
			hdlc_empty_fifo(bch, len);
			if (!bch->rx_skb)
				goto handle_tx;
			if ((stat & HDLC_STAT_RME) || test_bit(FLG_TRANSPARENT,
			    &bch->Flags)) {
				if (((stat & HDLC_STAT_CRCVFRRAB) ==
				    HDLC_STAT_CRCVFR) ||
				    test_bit(FLG_TRANSPARENT, &bch->Flags)) {
					recv_Bchannel(bch, 0);
				} else {
					pr_debug("%s: got invalid frame\n",
						fc->name);
					skb_trim(bch->rx_skb, 0);
				}
			}
		}
	}
handle_tx:
	if (stat & HDLC_INT_XDU) {
		/* Here we lost an TX interrupt, so
		 * restart transmitting the whole frame on HDLC
		 * in transparent mode we send the next data
		 */
		if (bch->tx_skb)
			pr_debug("%s: ch%d XDU len(%d) idx(%d) Flags(%lx)\n",
				fc->name, bch->nr, bch->tx_skb->len,
				bch->tx_idx, bch->Flags);
		else
			pr_debug("%s: ch%d XDU no tx_skb Flags(%lx)\n",
				fc->name, bch->nr, bch->Flags);
		if (bch->tx_skb && bch->tx_skb->len) {
			if (!test_bit(FLG_TRANSPARENT, &bch->Flags))
				bch->tx_idx = 0;
		}
		hdlc->ctrl.sr.xml = 0;
		hdlc->ctrl.sr.cmd |= HDLC_CMD_XRS;
		write_ctrl(bch, 1);
		hdlc->ctrl.sr.cmd &= ~HDLC_CMD_XRS;
		HDLC_irq_xpr(bch);
		return;
	} else if (stat & HDLC_INT_XPR)
		HDLC_irq_xpr(bch);
}