#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tcf_result {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  drops; int /*<<< orphan*/  overlimits; } ;
struct TYPE_5__ {scalar_t__ bps; } ;
struct TYPE_4__ {int /*<<< orphan*/  packets; int /*<<< orphan*/  bytes; } ;
struct tcf_police {scalar_t__ tcfp_ewma_rate; scalar_t__ tcf_action; scalar_t__ tcfp_mtu; int tcfp_result; long tcfp_burst; long tcfp_ptoks; long tcfp_toks; int /*<<< orphan*/  tcf_lock; TYPE_3__ tcf_qstats; int /*<<< orphan*/  tcfp_t_c; scalar_t__ tcfp_P_tab; int /*<<< orphan*/ * tcfp_R_tab; TYPE_2__ tcf_rate_est; TYPE_1__ tcf_bstats; } ;
struct tc_action {struct tcf_police* priv; } ;
struct sk_buff {int dummy; } ;
typedef  int /*<<< orphan*/  psched_time_t ;

/* Variables and functions */
 scalar_t__ L2T (struct tcf_police*,scalar_t__) ; 
 scalar_t__ L2T_P (struct tcf_police*,scalar_t__) ; 
 scalar_t__ TC_ACT_SHOT ; 
 int /*<<< orphan*/  psched_get_time () ; 
 long psched_tdiff_bounded (int /*<<< orphan*/ ,int /*<<< orphan*/ ,long) ; 
 scalar_t__ qdisc_pkt_len (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tcf_act_police(struct sk_buff *skb, struct tc_action *a,
			  struct tcf_result *res)
{
	struct tcf_police *police = a->priv;
	psched_time_t now;
	long toks;
	long ptoks = 0;

	spin_lock(&police->tcf_lock);

	police->tcf_bstats.bytes += qdisc_pkt_len(skb);
	police->tcf_bstats.packets++;

	if (police->tcfp_ewma_rate &&
	    police->tcf_rate_est.bps >= police->tcfp_ewma_rate) {
		police->tcf_qstats.overlimits++;
		if (police->tcf_action == TC_ACT_SHOT)
			police->tcf_qstats.drops++;
		spin_unlock(&police->tcf_lock);
		return police->tcf_action;
	}

	if (qdisc_pkt_len(skb) <= police->tcfp_mtu) {
		if (police->tcfp_R_tab == NULL) {
			spin_unlock(&police->tcf_lock);
			return police->tcfp_result;
		}

		now = psched_get_time();
		toks = psched_tdiff_bounded(now, police->tcfp_t_c,
					    police->tcfp_burst);
		if (police->tcfp_P_tab) {
			ptoks = toks + police->tcfp_ptoks;
			if (ptoks > (long)L2T_P(police, police->tcfp_mtu))
				ptoks = (long)L2T_P(police, police->tcfp_mtu);
			ptoks -= L2T_P(police, qdisc_pkt_len(skb));
		}
		toks += police->tcfp_toks;
		if (toks > (long)police->tcfp_burst)
			toks = police->tcfp_burst;
		toks -= L2T(police, qdisc_pkt_len(skb));
		if ((toks|ptoks) >= 0) {
			police->tcfp_t_c = now;
			police->tcfp_toks = toks;
			police->tcfp_ptoks = ptoks;
			spin_unlock(&police->tcf_lock);
			return police->tcfp_result;
		}
	}

	police->tcf_qstats.overlimits++;
	if (police->tcf_action == TC_ACT_SHOT)
		police->tcf_qstats.drops++;
	spin_unlock(&police->tcf_lock);
	return police->tcf_action;
}