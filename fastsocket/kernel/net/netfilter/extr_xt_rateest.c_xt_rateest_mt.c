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
typedef  scalar_t__ u_int32_t ;
struct xt_rateest_match_info {int flags; int mode; TYPE_2__* est2; scalar_t__ pps2; scalar_t__ bps2; TYPE_1__* est1; scalar_t__ pps1; scalar_t__ bps1; } ;
struct xt_match_param {struct xt_rateest_match_info* matchinfo; } ;
struct sk_buff {int dummy; } ;
struct gnet_stats_rate_est {scalar_t__ pps; scalar_t__ bps; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; struct gnet_stats_rate_est rstats; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; struct gnet_stats_rate_est rstats; } ;

/* Variables and functions */
 int XT_RATEEST_MATCH_ABS ; 
 int XT_RATEEST_MATCH_BPS ; 
 int XT_RATEEST_MATCH_DELTA ; 
#define  XT_RATEEST_MATCH_EQ 130 
#define  XT_RATEEST_MATCH_GT 129 
 int XT_RATEEST_MATCH_INVERT ; 
#define  XT_RATEEST_MATCH_LT 128 
 int XT_RATEEST_MATCH_PPS ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
xt_rateest_mt(const struct sk_buff *skb, const struct xt_match_param *par)
{
	const struct xt_rateest_match_info *info = par->matchinfo;
	struct gnet_stats_rate_est *r;
	u_int32_t bps1, bps2, pps1, pps2;
	bool ret = true;

	spin_lock_bh(&info->est1->lock);
	r = &info->est1->rstats;
	if (info->flags & XT_RATEEST_MATCH_DELTA) {
		bps1 = info->bps1 >= r->bps ? info->bps1 - r->bps : 0;
		pps1 = info->pps1 >= r->pps ? info->pps1 - r->pps : 0;
	} else {
		bps1 = r->bps;
		pps1 = r->pps;
	}
	spin_unlock_bh(&info->est1->lock);

	if (info->flags & XT_RATEEST_MATCH_ABS) {
		bps2 = info->bps2;
		pps2 = info->pps2;
	} else {
		spin_lock_bh(&info->est2->lock);
		r = &info->est2->rstats;
		if (info->flags & XT_RATEEST_MATCH_DELTA) {
			bps2 = info->bps2 >= r->bps ? info->bps2 - r->bps : 0;
			pps2 = info->pps2 >= r->pps ? info->pps2 - r->pps : 0;
		} else {
			bps2 = r->bps;
			pps2 = r->pps;
		}
		spin_unlock_bh(&info->est2->lock);
	}

	switch (info->mode) {
	case XT_RATEEST_MATCH_LT:
		if (info->flags & XT_RATEEST_MATCH_BPS)
			ret &= bps1 < bps2;
		if (info->flags & XT_RATEEST_MATCH_PPS)
			ret &= pps1 < pps2;
		break;
	case XT_RATEEST_MATCH_GT:
		if (info->flags & XT_RATEEST_MATCH_BPS)
			ret &= bps1 > bps2;
		if (info->flags & XT_RATEEST_MATCH_PPS)
			ret &= pps1 > pps2;
		break;
	case XT_RATEEST_MATCH_EQ:
		if (info->flags & XT_RATEEST_MATCH_BPS)
			ret &= bps1 == bps2;
		if (info->flags & XT_RATEEST_MATCH_PPS)
			ret &= pps1 == pps2;
		break;
	}

	ret ^= info->flags & XT_RATEEST_MATCH_INVERT ? true : false;
	return ret;
}