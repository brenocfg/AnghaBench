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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_5__ {int tx_idx; int nr; int debug; TYPE_1__* tx_skb; int /*<<< orphan*/  Flags; } ;
struct hscx_hw {int fifo_size; int /*<<< orphan*/  log; TYPE_3__* ip; TYPE_2__ bch; scalar_t__ off; } ;
struct TYPE_6__ {char* name; int type; int /*<<< orphan*/  hw; int /*<<< orphan*/  (* write_fifo ) (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int) ;} ;
struct TYPE_4__ {int len; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int DEBUG_HW_BFIFO ; 
 int /*<<< orphan*/  DUMP_PREFIX_OFFSET ; 
 int /*<<< orphan*/  FLG_TRANSPARENT ; 
 scalar_t__ IPACX_XFIFOB ; 
 int IPAC_TYPE_IPACX ; 
 int /*<<< orphan*/  hscx_cmdr (struct hscx_hw*,int) ; 
 int /*<<< orphan*/  pr_debug (char*,char*,int,int,int,int) ; 
 int /*<<< orphan*/  print_hex_dump_bytes (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int,char*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  waitforXFW (struct hscx_hw*) ; 

__attribute__((used)) static void
hscx_fill_fifo(struct hscx_hw *hscx)
{
	int count, more;
	u8 *p;

	if (!hscx->bch.tx_skb)
		return;
	count = hscx->bch.tx_skb->len - hscx->bch.tx_idx;
	if (count <= 0)
		return;
	p = hscx->bch.tx_skb->data + hscx->bch.tx_idx;

	more = test_bit(FLG_TRANSPARENT, &hscx->bch.Flags) ? 1 : 0;
	if (count > hscx->fifo_size) {
		count = hscx->fifo_size;
		more = 1;
	}
	pr_debug("%s: B%1d %d/%d/%d\n", hscx->ip->name, hscx->bch.nr, count,
		hscx->bch.tx_idx, hscx->bch.tx_skb->len);
	hscx->bch.tx_idx += count;

	if (hscx->ip->type & IPAC_TYPE_IPACX)
		hscx->ip->write_fifo(hscx->ip->hw,
			hscx->off + IPACX_XFIFOB, p, count);
	else {
		waitforXFW(hscx);
		hscx->ip->write_fifo(hscx->ip->hw,
			hscx->off, p, count);
	}
	hscx_cmdr(hscx, more ? 0x08 : 0x0a);

	if (hscx->bch.debug & DEBUG_HW_BFIFO) {
		snprintf(hscx->log, 64, "B%1d-send %s %d ",
			hscx->bch.nr, hscx->ip->name, count);
		print_hex_dump_bytes(hscx->log, DUMP_PREFIX_OFFSET, p, count);
	}
}