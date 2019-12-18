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
struct tcf_t {void* expires; void* lastuse; void* install; int /*<<< orphan*/  action; int /*<<< orphan*/  bindcnt; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  index; } ;
struct TYPE_2__ {scalar_t__ expires; scalar_t__ lastuse; scalar_t__ install; } ;
struct tcf_defact {TYPE_1__ tcf_tm; int /*<<< orphan*/  tcfd_defdata; int /*<<< orphan*/  tcf_action; int /*<<< orphan*/  tcf_bindcnt; int /*<<< orphan*/  tcf_refcnt; int /*<<< orphan*/  tcf_index; } ;
struct tc_defact {void* expires; void* lastuse; void* install; int /*<<< orphan*/  action; int /*<<< orphan*/  bindcnt; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  index; } ;
struct tc_action {struct tcf_defact* priv; } ;
struct sk_buff {int len; } ;
typedef  int /*<<< orphan*/  opt ;

/* Variables and functions */
 int /*<<< orphan*/  NLA_PUT (struct sk_buff*,int /*<<< orphan*/ ,int,struct tcf_t*) ; 
 int /*<<< orphan*/  NLA_PUT_STRING (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCA_DEF_DATA ; 
 int /*<<< orphan*/  TCA_DEF_PARMS ; 
 int /*<<< orphan*/  TCA_DEF_TM ; 
 scalar_t__ jiffies ; 
 void* jiffies_to_clock_t (scalar_t__) ; 
 int /*<<< orphan*/  nlmsg_trim (struct sk_buff*,unsigned char*) ; 
 unsigned char* skb_tail_pointer (struct sk_buff*) ; 

__attribute__((used)) static inline int tcf_simp_dump(struct sk_buff *skb, struct tc_action *a,
				int bind, int ref)
{
	unsigned char *b = skb_tail_pointer(skb);
	struct tcf_defact *d = a->priv;
	struct tc_defact opt = {
		.index   = d->tcf_index,
		.refcnt  = d->tcf_refcnt - ref,
		.bindcnt = d->tcf_bindcnt - bind,
		.action  = d->tcf_action,
	};
	struct tcf_t t;

	NLA_PUT(skb, TCA_DEF_PARMS, sizeof(opt), &opt);
	NLA_PUT_STRING(skb, TCA_DEF_DATA, d->tcfd_defdata);
	t.install = jiffies_to_clock_t(jiffies - d->tcf_tm.install);
	t.lastuse = jiffies_to_clock_t(jiffies - d->tcf_tm.lastuse);
	t.expires = jiffies_to_clock_t(d->tcf_tm.expires);
	NLA_PUT(skb, TCA_DEF_TM, sizeof(t), &t);
	return skb->len;

nla_put_failure:
	nlmsg_trim(skb, b);
	return -1;
}