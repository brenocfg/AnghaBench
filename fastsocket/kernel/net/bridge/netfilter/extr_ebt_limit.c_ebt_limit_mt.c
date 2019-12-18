#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct xt_match_param {scalar_t__ matchinfo; } ;
struct sk_buff {int dummy; } ;
struct ebt_limit_info {scalar_t__ credit; scalar_t__ credit_cap; scalar_t__ cost; int /*<<< orphan*/  prev; } ;

/* Variables and functions */
 unsigned long CREDITS_PER_JIFFY ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  limit_lock ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 unsigned long xchg (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static bool
ebt_limit_mt(const struct sk_buff *skb, const struct xt_match_param *par)
{
	struct ebt_limit_info *info = (void *)par->matchinfo;
	unsigned long now = jiffies;

	spin_lock_bh(&limit_lock);
	info->credit += (now - xchg(&info->prev, now)) * CREDITS_PER_JIFFY;
	if (info->credit > info->credit_cap)
		info->credit = info->credit_cap;

	if (info->credit >= info->cost) {
		/* We're not limited. */
		info->credit -= info->cost;
		spin_unlock_bh(&limit_lock);
		return true;
	}

	spin_unlock_bh(&limit_lock);
	return false;
}