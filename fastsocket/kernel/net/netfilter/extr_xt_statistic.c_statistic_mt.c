#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  every; } ;
struct TYPE_5__ {int probability; } ;
struct TYPE_7__ {TYPE_2__ nth; TYPE_1__ random; } ;
struct xt_statistic_info {int flags; int mode; TYPE_4__* master; TYPE_3__ u; } ;
struct xt_match_param {struct xt_statistic_info* matchinfo; } ;
struct sk_buff {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int XT_STATISTIC_INVERT ; 
#define  XT_STATISTIC_MODE_NTH 129 
#define  XT_STATISTIC_MODE_RANDOM 128 
 int net_random () ; 
 int /*<<< orphan*/  nth_lock ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
statistic_mt(const struct sk_buff *skb, const struct xt_match_param *par)
{
	const struct xt_statistic_info *info = par->matchinfo;
	bool ret = info->flags & XT_STATISTIC_INVERT;

	switch (info->mode) {
	case XT_STATISTIC_MODE_RANDOM:
		if ((net_random() & 0x7FFFFFFF) < info->u.random.probability)
			ret = !ret;
		break;
	case XT_STATISTIC_MODE_NTH:
		spin_lock_bh(&nth_lock);
		if (info->master->count++ == info->u.nth.every) {
			info->master->count = 0;
			ret = !ret;
		}
		spin_unlock_bh(&nth_lock);
		break;
	}

	return ret;
}