#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sk_buff {int dummy; } ;
struct layer2 {unsigned int va; size_t sow; int window; int /*<<< orphan*/  tmp_queue; int /*<<< orphan*/ ** windowar; int /*<<< orphan*/  flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLG_MOD128 ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_trim (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
setva(struct layer2 *l2, unsigned int nr)
{
	struct sk_buff	*skb;

	while (l2->va != nr) {
		l2->va++;
		if (test_bit(FLG_MOD128, &l2->flag))
			l2->va %= 128;
		else
			l2->va %= 8;
		if (l2->windowar[l2->sow]) {
			skb_trim(l2->windowar[l2->sow], 0);
			skb_queue_tail(&l2->tmp_queue, l2->windowar[l2->sow]);
			l2->windowar[l2->sow] = NULL;
		}
		l2->sow = (l2->sow + 1) % l2->window;
	}
	skb = skb_dequeue(&l2->tmp_queue);
	while (skb) {
		dev_kfree_skb(skb);
		skb = skb_dequeue(&l2->tmp_queue);
	}
}