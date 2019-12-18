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
struct tcf_result {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  packets; int /*<<< orphan*/  bytes; } ;
struct TYPE_3__ {int /*<<< orphan*/  lastuse; } ;
struct tcf_defact {int tcf_action; int /*<<< orphan*/  tcf_lock; TYPE_2__ tcf_bstats; scalar_t__ tcfd_defdata; TYPE_1__ tcf_tm; } ;
struct tc_action {struct tcf_defact* priv; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  pr_info (char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ qdisc_pkt_len (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tcf_simp(struct sk_buff *skb, struct tc_action *a, struct tcf_result *res)
{
	struct tcf_defact *d = a->priv;

	spin_lock(&d->tcf_lock);
	d->tcf_tm.lastuse = jiffies;
	d->tcf_bstats.bytes += qdisc_pkt_len(skb);
	d->tcf_bstats.packets++;

	/* print policy string followed by _ then packet count
	 * Example if this was the 3rd packet and the string was "hello"
	 * then it would look like "hello_3" (without quotes)
	 **/
	pr_info("simple: %s_%d\n",
	       (char *)d->tcfd_defdata, d->tcf_bstats.packets);
	spin_unlock(&d->tcf_lock);
	return d->tcf_action;
}