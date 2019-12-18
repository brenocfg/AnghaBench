#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ tx_idx; TYPE_2__* tx_skb; int /*<<< orphan*/  Flags; } ;
struct hscx_hw {TYPE_1__ bch; } ;
struct TYPE_5__ {scalar_t__ len; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLG_TRANSPARENT ; 
 int /*<<< orphan*/  confirm_Bsend (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_kfree_skb (TYPE_2__*) ; 
 scalar_t__ get_next_bframe (TYPE_1__*) ; 
 int /*<<< orphan*/  hscx_fill_fifo (struct hscx_hw*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
hscx_xpr(struct hscx_hw *hx)
{
	if (hx->bch.tx_skb && hx->bch.tx_idx < hx->bch.tx_skb->len)
		hscx_fill_fifo(hx);
	else {
		if (hx->bch.tx_skb) {
			/* send confirm, on trans, free on hdlc. */
			if (test_bit(FLG_TRANSPARENT, &hx->bch.Flags))
				confirm_Bsend(&hx->bch);
			dev_kfree_skb(hx->bch.tx_skb);
		}
		if (get_next_bframe(&hx->bch))
			hscx_fill_fifo(hx);
	}
}