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
typedef  int /*<<< orphan*/  t ;
struct tcf_t {int nkeys; void* expires; void* lastuse; void* install; scalar_t__ bindcnt; scalar_t__ refcnt; int /*<<< orphan*/  action; int /*<<< orphan*/  flags; int /*<<< orphan*/  index; int /*<<< orphan*/  keys; } ;
struct TYPE_2__ {scalar_t__ expires; scalar_t__ lastuse; scalar_t__ install; } ;
struct tcf_pedit {int tcfp_nkeys; TYPE_1__ tcf_tm; scalar_t__ tcf_bindcnt; scalar_t__ tcf_refcnt; int /*<<< orphan*/  tcf_action; int /*<<< orphan*/  tcfp_flags; int /*<<< orphan*/  tcf_index; int /*<<< orphan*/  tcfp_keys; } ;
struct tc_pedit_key {int dummy; } ;
struct tc_pedit {int nkeys; void* expires; void* lastuse; void* install; scalar_t__ bindcnt; scalar_t__ refcnt; int /*<<< orphan*/  action; int /*<<< orphan*/  flags; int /*<<< orphan*/  index; int /*<<< orphan*/  keys; } ;
struct tc_action {struct tcf_pedit* priv; } ;
struct sk_buff {int len; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  NLA_PUT (struct sk_buff*,int /*<<< orphan*/ ,int,struct tcf_t*) ; 
 int /*<<< orphan*/  TCA_PEDIT_PARMS ; 
 int /*<<< orphan*/  TCA_PEDIT_TM ; 
 scalar_t__ jiffies ; 
 void* jiffies_to_clock_t (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct tcf_t*) ; 
 struct tcf_t* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nlmsg_trim (struct sk_buff*,unsigned char*) ; 
 unsigned char* skb_tail_pointer (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int tcf_pedit_dump(struct sk_buff *skb, struct tc_action *a,
			  int bind, int ref)
{
	unsigned char *b = skb_tail_pointer(skb);
	struct tcf_pedit *p = a->priv;
	struct tc_pedit *opt;
	struct tcf_t t;
	int s;

	s = sizeof(*opt) + p->tcfp_nkeys * sizeof(struct tc_pedit_key);

	/* netlink spinlocks held above us - must use ATOMIC */
	opt = kzalloc(s, GFP_ATOMIC);
	if (unlikely(!opt))
		return -ENOBUFS;

	memcpy(opt->keys, p->tcfp_keys,
	       p->tcfp_nkeys * sizeof(struct tc_pedit_key));
	opt->index = p->tcf_index;
	opt->nkeys = p->tcfp_nkeys;
	opt->flags = p->tcfp_flags;
	opt->action = p->tcf_action;
	opt->refcnt = p->tcf_refcnt - ref;
	opt->bindcnt = p->tcf_bindcnt - bind;

	NLA_PUT(skb, TCA_PEDIT_PARMS, s, opt);
	t.install = jiffies_to_clock_t(jiffies - p->tcf_tm.install);
	t.lastuse = jiffies_to_clock_t(jiffies - p->tcf_tm.lastuse);
	t.expires = jiffies_to_clock_t(p->tcf_tm.expires);
	NLA_PUT(skb, TCA_PEDIT_TM, sizeof(t), &t);
	kfree(opt);
	return skb->len;

nla_put_failure:
	nlmsg_trim(skb, b);
	kfree(opt);
	return -1;
}