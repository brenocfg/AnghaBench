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
struct tcf_t {void* expires; void* lastuse; void* install; scalar_t__ ptype; int /*<<< orphan*/  pval; int /*<<< orphan*/  paction; int /*<<< orphan*/  action; int /*<<< orphan*/  bindcnt; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  index; } ;
struct TYPE_2__ {scalar_t__ expires; scalar_t__ lastuse; scalar_t__ install; } ;
struct tcf_gact {TYPE_1__ tcf_tm; scalar_t__ tcfg_ptype; int /*<<< orphan*/  tcfg_pval; int /*<<< orphan*/  tcfg_paction; int /*<<< orphan*/  tcf_action; int /*<<< orphan*/  tcf_bindcnt; int /*<<< orphan*/  tcf_refcnt; int /*<<< orphan*/  tcf_index; } ;
struct tc_gact_p {void* expires; void* lastuse; void* install; scalar_t__ ptype; int /*<<< orphan*/  pval; int /*<<< orphan*/  paction; int /*<<< orphan*/  action; int /*<<< orphan*/  bindcnt; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  index; } ;
struct tc_gact {void* expires; void* lastuse; void* install; scalar_t__ ptype; int /*<<< orphan*/  pval; int /*<<< orphan*/  paction; int /*<<< orphan*/  action; int /*<<< orphan*/  bindcnt; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  index; } ;
struct tc_action {struct tcf_gact* priv; } ;
struct sk_buff {int len; } ;
typedef  int /*<<< orphan*/  p_opt ;
typedef  int /*<<< orphan*/  opt ;

/* Variables and functions */
 int /*<<< orphan*/  NLA_PUT (struct sk_buff*,int /*<<< orphan*/ ,int,struct tcf_t*) ; 
 int /*<<< orphan*/  TCA_GACT_PARMS ; 
 int /*<<< orphan*/  TCA_GACT_PROB ; 
 int /*<<< orphan*/  TCA_GACT_TM ; 
 scalar_t__ jiffies ; 
 void* jiffies_to_clock_t (scalar_t__) ; 
 int /*<<< orphan*/  nlmsg_trim (struct sk_buff*,unsigned char*) ; 
 unsigned char* skb_tail_pointer (struct sk_buff*) ; 

__attribute__((used)) static int tcf_gact_dump(struct sk_buff *skb, struct tc_action *a, int bind, int ref)
{
	unsigned char *b = skb_tail_pointer(skb);
	struct tcf_gact *gact = a->priv;
	struct tc_gact opt = {
		.index   = gact->tcf_index,
		.refcnt  = gact->tcf_refcnt - ref,
		.bindcnt = gact->tcf_bindcnt - bind,
		.action  = gact->tcf_action,
	};
	struct tcf_t t;

	NLA_PUT(skb, TCA_GACT_PARMS, sizeof(opt), &opt);
#ifdef CONFIG_GACT_PROB
	if (gact->tcfg_ptype) {
		struct tc_gact_p p_opt = {
			.paction = gact->tcfg_paction,
			.pval    = gact->tcfg_pval,
			.ptype   = gact->tcfg_ptype,
		};

		NLA_PUT(skb, TCA_GACT_PROB, sizeof(p_opt), &p_opt);
	}
#endif
	t.install = jiffies_to_clock_t(jiffies - gact->tcf_tm.install);
	t.lastuse = jiffies_to_clock_t(jiffies - gact->tcf_tm.lastuse);
	t.expires = jiffies_to_clock_t(gact->tcf_tm.expires);
	NLA_PUT(skb, TCA_GACT_TM, sizeof(t), &t);
	return skb->len;

nla_put_failure:
	nlmsg_trim(skb, b);
	return -1;
}