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
struct TYPE_2__ {int family; } ;
struct xfrm_userpolicy_info {int share; int action; int /*<<< orphan*/  dir; TYPE_1__ sel; } ;

/* Variables and functions */
#define  AF_INET 135 
#define  AF_INET6 134 
 int EAFNOSUPPORT ; 
 int EINVAL ; 
#define  XFRM_POLICY_ALLOW 133 
#define  XFRM_POLICY_BLOCK 132 
#define  XFRM_SHARE_ANY 131 
#define  XFRM_SHARE_SESSION 130 
#define  XFRM_SHARE_UNIQUE 129 
#define  XFRM_SHARE_USER 128 
 int verify_policy_dir (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int verify_newpolicy_info(struct xfrm_userpolicy_info *p)
{
	switch (p->share) {
	case XFRM_SHARE_ANY:
	case XFRM_SHARE_SESSION:
	case XFRM_SHARE_USER:
	case XFRM_SHARE_UNIQUE:
		break;

	default:
		return -EINVAL;
	}

	switch (p->action) {
	case XFRM_POLICY_ALLOW:
	case XFRM_POLICY_BLOCK:
		break;

	default:
		return -EINVAL;
	}

	switch (p->sel.family) {
	case AF_INET:
		break;

	case AF_INET6:
#if defined(CONFIG_IPV6) || defined(CONFIG_IPV6_MODULE)
		break;
#else
		return  -EAFNOSUPPORT;
#endif

	default:
		return -EINVAL;
	}

	return verify_policy_dir(p->dir);
}