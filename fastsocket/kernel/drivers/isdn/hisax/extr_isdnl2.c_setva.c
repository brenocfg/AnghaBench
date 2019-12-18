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
typedef  int /*<<< orphan*/  u_long ;
struct TYPE_3__ {int /*<<< orphan*/  flag; } ;
struct Layer2 {unsigned int va; size_t sow; int window; int /*<<< orphan*/  lock; TYPE_2__** windowar; int /*<<< orphan*/  flag; } ;
struct PStack {TYPE_1__ lli; struct Layer2 l2; } ;
struct TYPE_4__ {int len; scalar_t__ pkt_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLG_LLI_L2WAKEUP ; 
 int /*<<< orphan*/  FLG_MOD128 ; 
 scalar_t__ PACKET_NOACK ; 
 int /*<<< orphan*/  dev_kfree_skb (TYPE_2__*) ; 
 int /*<<< orphan*/  lli_writewakeup (struct PStack*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
setva(struct PStack *st, unsigned int nr)
{
	struct Layer2 *l2 = &st->l2;
	int len;
	u_long flags;

	spin_lock_irqsave(&l2->lock, flags);
	while (l2->va != nr) {
		(l2->va)++;
		if(test_bit(FLG_MOD128, &l2->flag))
			l2->va %= 128;
		else
			l2->va %= 8;
		len = l2->windowar[l2->sow]->len;
		if (PACKET_NOACK == l2->windowar[l2->sow]->pkt_type)
			len = -1;
		dev_kfree_skb(l2->windowar[l2->sow]);
		l2->windowar[l2->sow] = NULL;
		l2->sow = (l2->sow + 1) % l2->window;
		spin_unlock_irqrestore(&l2->lock, flags);
		if (test_bit(FLG_LLI_L2WAKEUP, &st->lli.flag) && (len >=0))
			lli_writewakeup(st, len);
		spin_lock_irqsave(&l2->lock, flags);
	}
	spin_unlock_irqrestore(&l2->lock, flags);
}