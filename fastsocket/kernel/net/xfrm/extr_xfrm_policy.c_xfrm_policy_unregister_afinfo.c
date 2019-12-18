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
struct xfrm_policy_afinfo {size_t family; int /*<<< orphan*/ * garbage_collect; struct dst_ops* dst_ops; } ;
struct dst_ops {int /*<<< orphan*/ * link_failure; int /*<<< orphan*/ * negative_advice; int /*<<< orphan*/ * check; int /*<<< orphan*/ * kmem_cachep; } ;

/* Variables and functions */
 int EAFNOSUPPORT ; 
 int EINVAL ; 
 size_t NPROTO ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (struct xfrm_policy_afinfo*,int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 
 scalar_t__ unlikely (int) ; 
 struct xfrm_policy_afinfo** xfrm_policy_afinfo ; 
 int /*<<< orphan*/  xfrm_policy_afinfo_lock ; 

int xfrm_policy_unregister_afinfo(struct xfrm_policy_afinfo *afinfo)
{
	int err = 0;
	if (unlikely(afinfo == NULL))
		return -EINVAL;
	if (unlikely(afinfo->family >= NPROTO))
		return -EAFNOSUPPORT;
	spin_lock(&xfrm_policy_afinfo_lock);
	if (likely(xfrm_policy_afinfo[afinfo->family] != NULL)) {
		if (unlikely(xfrm_policy_afinfo[afinfo->family] != afinfo))
			err = -EINVAL;
		else
			RCU_INIT_POINTER(xfrm_policy_afinfo[afinfo->family],
					 NULL);
	}
	spin_unlock(&xfrm_policy_afinfo_lock);
	if (!err) {
		struct dst_ops *dst_ops = afinfo->dst_ops;

		synchronize_rcu();

		dst_ops->kmem_cachep = NULL;
		dst_ops->check = NULL;
		dst_ops->negative_advice = NULL;
		dst_ops->link_failure = NULL;
		afinfo->garbage_collect = NULL;
	}
	return err;
}