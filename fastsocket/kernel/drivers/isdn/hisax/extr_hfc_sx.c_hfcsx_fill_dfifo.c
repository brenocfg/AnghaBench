#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct IsdnCardState {TYPE_1__* tx_skb; } ;
struct TYPE_3__ {scalar_t__ len; } ;

/* Variables and functions */
 int /*<<< orphan*/  HFCSX_SEL_D_TX ; 
 int /*<<< orphan*/  dev_kfree_skb_any (TYPE_1__*) ; 
 scalar_t__ write_fifo (struct IsdnCardState*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
hfcsx_fill_dfifo(struct IsdnCardState *cs)
{
	if (!cs->tx_skb)
		return;
	if (cs->tx_skb->len <= 0)
		return;

	if (write_fifo(cs, cs->tx_skb, HFCSX_SEL_D_TX, 0)) {
	  dev_kfree_skb_any(cs->tx_skb);
	  cs->tx_skb = NULL;
	}
	return;
}