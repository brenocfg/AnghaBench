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
struct TYPE_4__ {int flags; int /*<<< orphan*/  dim; } ;
struct TYPE_5__ {TYPE_1__ compat; } ;
struct TYPE_6__ {TYPE_2__ u; int /*<<< orphan*/  index; } ;
struct xt_set_info_match_v0 {TYPE_3__ match_set; } ;
struct xt_match_param {int /*<<< orphan*/  family; struct xt_set_info_match_v0* matchinfo; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int IPSET_INV_MATCH ; 
 int match_set (int /*<<< orphan*/ ,struct sk_buff const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static bool
set_match_v0(const struct sk_buff *skb, const struct xt_match_param *par)
{
	const struct xt_set_info_match_v0 *info = par->matchinfo;

	return match_set(info->match_set.index, skb, par->family,
			 info->match_set.u.compat.dim,
			 info->match_set.u.compat.flags,
			 info->match_set.u.compat.flags & IPSET_INV_MATCH);
}