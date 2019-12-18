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
struct xfrm_userpolicy_info {int dummy; } ;
struct TYPE_2__ {int dead; } ;
struct xfrm_policy {TYPE_1__ walk; int /*<<< orphan*/  mark; int /*<<< orphan*/  type; } ;
struct nlattr {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  copy_from_user_policy (struct xfrm_policy*,struct xfrm_userpolicy_info*) ; 
 int copy_from_user_policy_type (int /*<<< orphan*/ *,struct nlattr**) ; 
 int copy_from_user_sec_ctx (struct xfrm_policy*,struct nlattr**) ; 
 int copy_from_user_tmpl (struct xfrm_policy*,struct nlattr**) ; 
 int /*<<< orphan*/  xfrm_mark_get (struct nlattr**,int /*<<< orphan*/ *) ; 
 struct xfrm_policy* xfrm_policy_alloc (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfrm_policy_destroy (struct xfrm_policy*) ; 

__attribute__((used)) static struct xfrm_policy *xfrm_policy_construct(struct net *net, struct xfrm_userpolicy_info *p, struct nlattr **attrs, int *errp)
{
	struct xfrm_policy *xp = xfrm_policy_alloc(net, GFP_KERNEL);
	int err;

	if (!xp) {
		*errp = -ENOMEM;
		return NULL;
	}

	copy_from_user_policy(xp, p);

	err = copy_from_user_policy_type(&xp->type, attrs);
	if (err)
		goto error;

	if (!(err = copy_from_user_tmpl(xp, attrs)))
		err = copy_from_user_sec_ctx(xp, attrs);
	if (err)
		goto error;

	xfrm_mark_get(attrs, &xp->mark);

	return xp;
 error:
	*errp = err;
	xp->walk.dead = 1;
	xfrm_policy_destroy(xp);
	return NULL;
}