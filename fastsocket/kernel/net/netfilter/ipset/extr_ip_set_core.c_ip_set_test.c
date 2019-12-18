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
typedef  scalar_t__ u8 ;
struct sk_buff {int dummy; } ;
struct ip_set {scalar_t__ family; int /*<<< orphan*/  lock; TYPE_2__* variant; TYPE_1__* type; int /*<<< orphan*/  name; } ;
typedef  size_t ip_set_id_t ;
struct TYPE_4__ {int (* kadt ) (struct ip_set*,struct sk_buff const*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ;} ;
struct TYPE_3__ {scalar_t__ dimension; } ;

/* Variables and functions */
 scalar_t__ AF_UNSPEC ; 
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int EAGAIN ; 
 int /*<<< orphan*/  IPSET_ADD ; 
 int /*<<< orphan*/  IPSET_TEST ; 
 struct ip_set** ip_set_list ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 
 int stub1 (struct ip_set*,struct sk_buff const*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 int stub2 (struct ip_set*,struct sk_buff const*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

int
ip_set_test(ip_set_id_t index, const struct sk_buff *skb,
	    u8 family, u8 dim, u8 flags)
{
	struct ip_set *set = ip_set_list[index];
	int ret = 0;

	BUG_ON(set == NULL);
	pr_debug("set %s, index %u\n", set->name, index);

	if (dim < set->type->dimension ||
	    !(family == set->family || set->family == AF_UNSPEC))
		return 0;

	read_lock_bh(&set->lock);
	ret = set->variant->kadt(set, skb, IPSET_TEST, family, dim, flags);
	read_unlock_bh(&set->lock);

	if (ret == -EAGAIN) {
		/* Type requests element to be completed */
		pr_debug("element must be competed, ADD is triggered\n");
		write_lock_bh(&set->lock);
		set->variant->kadt(set, skb, IPSET_ADD, family, dim, flags);
		write_unlock_bh(&set->lock);
		ret = 1;
	}

	/* Convert error codes to nomatch */
	return (ret < 0 ? 0 : ret);
}