#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct xt_target_param {int /*<<< orphan*/  family; struct xt_set_info_target_v0* targinfo; } ;
struct TYPE_10__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  dim; } ;
struct TYPE_11__ {TYPE_4__ compat; } ;
struct TYPE_12__ {scalar_t__ index; TYPE_5__ u; } ;
struct TYPE_7__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  dim; } ;
struct TYPE_8__ {TYPE_1__ compat; } ;
struct TYPE_9__ {scalar_t__ index; TYPE_2__ u; } ;
struct xt_set_info_target_v0 {TYPE_6__ del_set; TYPE_3__ add_set; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 scalar_t__ IPSET_INVALID_ID ; 
 unsigned int XT_CONTINUE ; 
 int /*<<< orphan*/  ip_set_add (scalar_t__,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_set_del (scalar_t__,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int
set_target_v0(struct sk_buff *skb, const struct xt_target_param *par)
{
	const struct xt_set_info_target_v0 *info = par->targinfo;

	if (info->add_set.index != IPSET_INVALID_ID)
		ip_set_add(info->add_set.index, skb, par->family,
			   info->add_set.u.compat.dim,
			   info->add_set.u.compat.flags);
	if (info->del_set.index != IPSET_INVALID_ID)
		ip_set_del(info->del_set.index, skb, par->family,
			   info->del_set.u.compat.dim,
			   info->del_set.u.compat.flags);

	return XT_CONTINUE;
}