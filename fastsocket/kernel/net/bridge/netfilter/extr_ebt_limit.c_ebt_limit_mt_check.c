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
struct xt_mtchk_param {struct ebt_limit_info* matchinfo; } ;
struct ebt_limit_info {int burst; int avg; scalar_t__ cost; scalar_t__ credit_cap; scalar_t__ credit; int /*<<< orphan*/  prev; } ;

/* Variables and functions */
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  printk (char*,int,int) ; 
 scalar_t__ user2credits (int) ; 

__attribute__((used)) static bool ebt_limit_mt_check(const struct xt_mtchk_param *par)
{
	struct ebt_limit_info *info = par->matchinfo;

	/* Check for overflow. */
	if (info->burst == 0 ||
	    user2credits(info->avg * info->burst) < user2credits(info->avg)) {
		printk("Overflow in ebt_limit, try lower: %u/%u\n",
			info->avg, info->burst);
		return false;
	}

	/* User avg in seconds * EBT_LIMIT_SCALE: convert to jiffies * 128. */
	info->prev = jiffies;
	info->credit = user2credits(info->avg * info->burst);
	info->credit_cap = user2credits(info->avg * info->burst);
	info->cost = user2credits(info->avg);
	return true;
}