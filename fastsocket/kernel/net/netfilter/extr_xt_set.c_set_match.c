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
struct TYPE_2__ {int flags; int /*<<< orphan*/  dim; int /*<<< orphan*/  index; } ;
struct xt_set_info_match {TYPE_1__ match_set; } ;
struct xt_match_param {int /*<<< orphan*/  family; struct xt_set_info_match* matchinfo; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int IPSET_INV_MATCH ; 
 int match_set (int /*<<< orphan*/ ,struct sk_buff const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static bool
set_match(const struct sk_buff *skb, const struct xt_match_param *par)
{
	const struct xt_set_info_match *info = par->matchinfo;

	return match_set(info->match_set.index, skb, par->family,
			 info->match_set.dim,
			 info->match_set.flags,
			 info->match_set.flags & IPSET_INV_MATCH);
}