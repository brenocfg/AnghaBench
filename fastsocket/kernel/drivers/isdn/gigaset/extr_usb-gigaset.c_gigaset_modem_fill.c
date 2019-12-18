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
struct cmdbuf_t {int dummy; } ;
struct TYPE_4__ {TYPE_1__* usb; } ;
struct cardstate {struct cmdbuf_t* cmdbuf; TYPE_2__ hw; struct bc_state* bcs; } ;
struct bc_state {scalar_t__ tx_skb; int /*<<< orphan*/  squeue; } ;
struct TYPE_3__ {scalar_t__ busy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_INTR ; 
 int /*<<< orphan*/  DEBUG_OUTPUT ; 
 int /*<<< orphan*/  gig_dbg (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ send_cb (struct cardstate*,struct cmdbuf_t*) ; 
 scalar_t__ skb_dequeue (int /*<<< orphan*/ *) ; 
 scalar_t__ write_modem (struct cardstate*) ; 

__attribute__((used)) static void gigaset_modem_fill(unsigned long data)
{
	struct cardstate *cs = (struct cardstate *) data;
	struct bc_state *bcs = &cs->bcs[0]; /* only one channel */
	struct cmdbuf_t *cb;
	int again;

	gig_dbg(DEBUG_OUTPUT, "modem_fill");

	if (cs->hw.usb->busy) {
		gig_dbg(DEBUG_OUTPUT, "modem_fill: busy");
		return;
	}

	do {
		again = 0;
		if (!bcs->tx_skb) { /* no skb is being sent */
			cb = cs->cmdbuf;
			if (cb) { /* commands to send? */
				gig_dbg(DEBUG_OUTPUT, "modem_fill: cb");
				if (send_cb(cs, cb) < 0) {
					gig_dbg(DEBUG_OUTPUT,
						"modem_fill: send_cb failed");
					again = 1; /* no callback will be
						      called! */
				}
			} else { /* skbs to send? */
				bcs->tx_skb = skb_dequeue(&bcs->squeue);
				if (bcs->tx_skb)
					gig_dbg(DEBUG_INTR,
						"Dequeued skb (Adr: %lx)!",
						(unsigned long) bcs->tx_skb);
			}
		}

		if (bcs->tx_skb) {
			gig_dbg(DEBUG_OUTPUT, "modem_fill: tx_skb");
			if (write_modem(cs) < 0) {
				gig_dbg(DEBUG_OUTPUT,
					"modem_fill: write_modem failed");
				// FIXME should we tell the LL?
				again = 1; /* no callback will be called! */
			}
		}
	} while (again);
}