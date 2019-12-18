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
typedef  int u8 ;
struct TYPE_6__ {int debug; TYPE_2__* rx_skb; int /*<<< orphan*/  nr; int /*<<< orphan*/  state; } ;
struct hscx_hw {int fifo_size; TYPE_3__ bch; TYPE_1__* ip; } ;
struct TYPE_5__ {int len; } ;
struct TYPE_4__ {int type; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int DEBUG_HW_BCHANNEL ; 
 int /*<<< orphan*/  IPACX_RBCLB ; 
 int /*<<< orphan*/  IPACX_RSTAB ; 
 int /*<<< orphan*/  IPAC_RBCLB ; 
 int /*<<< orphan*/  IPAC_RSTAB ; 
 int IPAC_TYPE_IPACX ; 
 int ReadHSCX (struct hscx_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hscx_cmdr (struct hscx_hw*,int) ; 
 int /*<<< orphan*/  hscx_empty_fifo (struct hscx_hw*,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_notice (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  recv_Bchannel (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_trim (TYPE_2__*,int) ; 

__attribute__((used)) static void
ipac_rme(struct hscx_hw *hx)
{
	int count;
	u8 rstab;

	if (hx->ip->type & IPAC_TYPE_IPACX)
		rstab = ReadHSCX(hx, IPACX_RSTAB);
	else
		rstab = ReadHSCX(hx, IPAC_RSTAB);
	pr_debug("%s: B%1d RSTAB %02x\n", hx->ip->name, hx->bch.nr, rstab);
	if ((rstab & 0xf0) != 0xa0) {
		/* !(VFR && !RDO && CRC && !RAB) */
		if (!(rstab & 0x80)) {
			if (hx->bch.debug & DEBUG_HW_BCHANNEL)
				pr_notice("%s: B%1d invalid frame\n",
					hx->ip->name, hx->bch.nr);
		}
		if (rstab & 0x40) {
			if (hx->bch.debug & DEBUG_HW_BCHANNEL)
				pr_notice("%s: B%1d RDO proto=%x\n",
					hx->ip->name, hx->bch.nr,
					hx->bch.state);
		}
		if (!(rstab & 0x20)) {
			if (hx->bch.debug & DEBUG_HW_BCHANNEL)
				pr_notice("%s: B%1d CRC error\n",
					hx->ip->name, hx->bch.nr);
		}
		hscx_cmdr(hx, 0x80); /* Do RMC */
		return;
	}
	if (hx->ip->type & IPAC_TYPE_IPACX)
		count = ReadHSCX(hx, IPACX_RBCLB);
	else
		count = ReadHSCX(hx, IPAC_RBCLB);
	count &= (hx->fifo_size - 1);
	if (count == 0)
		count = hx->fifo_size;
	hscx_empty_fifo(hx, count);
	if (!hx->bch.rx_skb)
		return;
	if (hx->bch.rx_skb->len < 2) {
		pr_debug("%s: B%1d frame to short %d\n",
			hx->ip->name, hx->bch.nr, hx->bch.rx_skb->len);
		skb_trim(hx->bch.rx_skb, 0);
	} else {
		skb_trim(hx->bch.rx_skb, hx->bch.rx_skb->len - 1);
		recv_Bchannel(&hx->bch, 0);
	}
}