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
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  hardware; } ;
struct PStack {TYPE_1__ l1; } ;

/* Variables and functions */
 int /*<<< orphan*/  HiSax_putstatus (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 

__attribute__((used)) static void
no_l3_proto(struct PStack *st, int pr, void *arg)
{
	struct sk_buff *skb = arg;

	HiSax_putstatus(st->l1.hardware, "L3", "no D protocol");
	if (skb) {
		dev_kfree_skb(skb);
	}
}