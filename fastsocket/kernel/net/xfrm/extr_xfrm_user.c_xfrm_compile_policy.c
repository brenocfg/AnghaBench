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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  family; } ;
struct xfrm_userpolicy_info {int dir; TYPE_1__ sel; } ;
struct xfrm_user_tmpl {int dummy; } ;
struct xfrm_policy {int /*<<< orphan*/  type; } ;
struct sock {int sk_family; } ;
struct net {int dummy; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int EINVAL ; 
 int ENOBUFS ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IPV6_XFRM_POLICY ; 
 int IP_XFRM_POLICY ; 
 int XFRM_POLICY_OUT ; 
 int /*<<< orphan*/  XFRM_POLICY_TYPE_MAIN ; 
 int /*<<< orphan*/  copy_from_user_policy (struct xfrm_policy*,struct xfrm_userpolicy_info*) ; 
 int /*<<< orphan*/  copy_templates (struct xfrm_policy*,struct xfrm_user_tmpl*,int) ; 
 struct net* sock_net (struct sock*) ; 
 scalar_t__ validate_tmpl (int,struct xfrm_user_tmpl*,int /*<<< orphan*/ ) ; 
 scalar_t__ verify_newpolicy_info (struct xfrm_userpolicy_info*) ; 
 struct xfrm_policy* xfrm_policy_alloc (struct net*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct xfrm_policy *xfrm_compile_policy(struct sock *sk, int opt,
					       u8 *data, int len, int *dir)
{
	struct net *net = sock_net(sk);
	struct xfrm_userpolicy_info *p = (struct xfrm_userpolicy_info *)data;
	struct xfrm_user_tmpl *ut = (struct xfrm_user_tmpl *) (p + 1);
	struct xfrm_policy *xp;
	int nr;

	switch (sk->sk_family) {
	case AF_INET:
		if (opt != IP_XFRM_POLICY) {
			*dir = -EOPNOTSUPP;
			return NULL;
		}
		break;
#if defined(CONFIG_IPV6) || defined(CONFIG_IPV6_MODULE)
	case AF_INET6:
		if (opt != IPV6_XFRM_POLICY) {
			*dir = -EOPNOTSUPP;
			return NULL;
		}
		break;
#endif
	default:
		*dir = -EINVAL;
		return NULL;
	}

	*dir = -EINVAL;

	if (len < sizeof(*p) ||
	    verify_newpolicy_info(p))
		return NULL;

	nr = ((len - sizeof(*p)) / sizeof(*ut));
	if (validate_tmpl(nr, ut, p->sel.family))
		return NULL;

	if (p->dir > XFRM_POLICY_OUT)
		return NULL;

	xp = xfrm_policy_alloc(net, GFP_KERNEL);
	if (xp == NULL) {
		*dir = -ENOBUFS;
		return NULL;
	}

	copy_from_user_policy(xp, p);
	xp->type = XFRM_POLICY_TYPE_MAIN;
	copy_templates(xp, ut, nr);

	*dir = p->dir;

	return xp;
}