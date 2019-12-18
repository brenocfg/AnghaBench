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
struct xfrm_policy_afinfo {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * ops; } ;
struct xfrm_dst {TYPE_1__ flo; } ;
struct dst_ops {int dummy; } ;
struct net {struct dst_ops xfrm6_dst_ops; struct dst_ops xfrm4_dst_ops; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOBUFS ; 
 struct xfrm_dst* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct xfrm_dst* dst_alloc (struct dst_ops*) ; 
 scalar_t__ likely (struct xfrm_dst*) ; 
 int /*<<< orphan*/  xfrm_bundle_fc_ops ; 
 struct xfrm_policy_afinfo* xfrm_policy_get_afinfo (int) ; 
 int /*<<< orphan*/  xfrm_policy_put_afinfo (struct xfrm_policy_afinfo*) ; 

__attribute__((used)) static inline struct xfrm_dst *xfrm_alloc_dst(struct net *net, int family)
{
	struct xfrm_policy_afinfo *afinfo = xfrm_policy_get_afinfo(family);
	struct dst_ops *dst_ops;
	struct xfrm_dst *xdst;

	if (!afinfo)
		return ERR_PTR(-EINVAL);

	switch (family) {
	case AF_INET:
		dst_ops = &net->xfrm4_dst_ops;
		break;
#if defined(CONFIG_IPV6) || defined(CONFIG_IPV6_MODULE)
	case AF_INET6:
		dst_ops = &net->xfrm6_dst_ops;
		break;
#endif
	default:
		BUG();
	}
	xdst = dst_alloc(dst_ops);
	xfrm_policy_put_afinfo(afinfo);

	if (likely(xdst))
		xdst->flo.ops = &xfrm_bundle_fc_ops;
	else
		xdst = ERR_PTR(-ENOBUFS);

	return xdst;
}