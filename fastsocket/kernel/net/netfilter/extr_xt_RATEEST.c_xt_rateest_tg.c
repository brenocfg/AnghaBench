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
struct xt_target_param {struct xt_rateest_target_info* targinfo; } ;
struct xt_rateest_target_info {TYPE_1__* est; } ;
struct sk_buff {scalar_t__ len; } ;
struct gnet_stats_basic_packed {int /*<<< orphan*/  packets; int /*<<< orphan*/  bytes; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; struct gnet_stats_basic_packed bstats; } ;

/* Variables and functions */
 unsigned int XT_CONTINUE ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned int
xt_rateest_tg(struct sk_buff *skb, const struct xt_target_param *par)
{
	const struct xt_rateest_target_info *info = par->targinfo;
	struct gnet_stats_basic_packed *stats = &info->est->bstats;

	spin_lock_bh(&info->est->lock);
	stats->bytes += skb->len;
	stats->packets++;
	spin_unlock_bh(&info->est->lock);

	return XT_CONTINUE;
}