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
struct xt_target_param {int /*<<< orphan*/  family; struct xt_set_info_target* targinfo; } ;
struct TYPE_3__ {scalar_t__ index; int /*<<< orphan*/  flags; int /*<<< orphan*/  dim; } ;
struct TYPE_4__ {scalar_t__ index; int /*<<< orphan*/  flags; int /*<<< orphan*/  dim; } ;
struct xt_set_info_target {TYPE_1__ del_set; TYPE_2__ add_set; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 scalar_t__ IPSET_INVALID_ID ; 
 unsigned int XT_CONTINUE ; 
 int /*<<< orphan*/  ip_set_add (scalar_t__,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_set_del (scalar_t__,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int
set_target(struct sk_buff *skb, const struct xt_target_param *par)
{
	const struct xt_set_info_target *info = par->targinfo;

	if (info->add_set.index != IPSET_INVALID_ID)
		ip_set_add(info->add_set.index,
			   skb, par->family,
			   info->add_set.dim,
			   info->add_set.flags);
	if (info->del_set.index != IPSET_INVALID_ID)
		ip_set_del(info->del_set.index,
			   skb, par->family,
			   info->del_set.dim,
			   info->del_set.flags);

	return XT_CONTINUE;
}