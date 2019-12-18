#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct isac {TYPE_1__* tx_skb; scalar_t__ tx_cnt; } ;
struct TYPE_2__ {scalar_t__ len; } ;

/* Variables and functions */
 int CONFIRM ; 
 int /*<<< orphan*/  D_L1L2 (struct isac*,int,int /*<<< orphan*/ *) ; 
 int PH_DATA ; 
 int /*<<< orphan*/  dev_kfree_skb_irq (TYPE_1__*) ; 
 int /*<<< orphan*/  isac_fill_fifo (struct isac*) ; 

__attribute__((used)) static inline void isac_xpr_interrupt(struct isac *isac)
{
	if (!isac->tx_skb)
		return;

	if (isac->tx_skb->len > 0) {
		isac_fill_fifo(isac);
		return;
	}
	dev_kfree_skb_irq(isac->tx_skb);
	isac->tx_cnt = 0;
	isac->tx_skb = NULL;
	D_L1L2(isac, PH_DATA | CONFIRM, NULL);
}