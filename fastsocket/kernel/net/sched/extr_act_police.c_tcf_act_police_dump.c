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
struct tcf_police {scalar_t__ tcfp_ewma_rate; scalar_t__ tcfp_result; TYPE_2__* tcfp_P_tab; TYPE_1__* tcfp_R_tab; int /*<<< orphan*/  tcf_bindcnt; int /*<<< orphan*/  tcf_refcnt; int /*<<< orphan*/  tcfp_burst; int /*<<< orphan*/  tcfp_mtu; int /*<<< orphan*/  tcf_action; int /*<<< orphan*/  tcf_index; } ;
struct tc_police {int /*<<< orphan*/  peakrate; int /*<<< orphan*/  rate; int /*<<< orphan*/  bindcnt; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  burst; int /*<<< orphan*/  mtu; int /*<<< orphan*/  action; int /*<<< orphan*/  index; } ;
struct tc_action {struct tcf_police* priv; } ;
struct sk_buff {int len; } ;
typedef  int /*<<< orphan*/  opt ;
struct TYPE_4__ {int /*<<< orphan*/  rate; } ;
struct TYPE_3__ {int /*<<< orphan*/  rate; } ;

/* Variables and functions */
 int /*<<< orphan*/  NLA_PUT (struct sk_buff*,int /*<<< orphan*/ ,int,struct tc_police*) ; 
 int /*<<< orphan*/  NLA_PUT_U32 (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  TCA_POLICE_AVRATE ; 
 int /*<<< orphan*/  TCA_POLICE_RESULT ; 
 int /*<<< orphan*/  TCA_POLICE_TBF ; 
 int /*<<< orphan*/  nlmsg_trim (struct sk_buff*,unsigned char*) ; 
 unsigned char* skb_tail_pointer (struct sk_buff*) ; 

__attribute__((used)) static int
tcf_act_police_dump(struct sk_buff *skb, struct tc_action *a, int bind, int ref)
{
	unsigned char *b = skb_tail_pointer(skb);
	struct tcf_police *police = a->priv;
	struct tc_police opt = {
		.index = police->tcf_index,
		.action = police->tcf_action,
		.mtu = police->tcfp_mtu,
		.burst = police->tcfp_burst,
		.refcnt = police->tcf_refcnt - ref,
		.bindcnt = police->tcf_bindcnt - bind,
	};

	if (police->tcfp_R_tab)
		opt.rate = police->tcfp_R_tab->rate;
	if (police->tcfp_P_tab)
		opt.peakrate = police->tcfp_P_tab->rate;
	NLA_PUT(skb, TCA_POLICE_TBF, sizeof(opt), &opt);
	if (police->tcfp_result)
		NLA_PUT_U32(skb, TCA_POLICE_RESULT, police->tcfp_result);
	if (police->tcfp_ewma_rate)
		NLA_PUT_U32(skb, TCA_POLICE_AVRATE, police->tcfp_ewma_rate);
	return skb->len;

nla_put_failure:
	nlmsg_trim(skb, b);
	return -1;
}