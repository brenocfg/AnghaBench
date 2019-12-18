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
typedef  int /*<<< orphan*/  xfrm_address_t ;
struct xfrm_policy_afinfo {int (* get_saddr ) (struct net*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
struct net {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int stub1 (struct net*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 struct xfrm_policy_afinfo* xfrm_policy_get_afinfo (unsigned short) ; 
 int /*<<< orphan*/  xfrm_policy_put_afinfo (struct xfrm_policy_afinfo*) ; 

__attribute__((used)) static int
xfrm_get_saddr(struct net *net, xfrm_address_t *local, xfrm_address_t *remote,
	       unsigned short family)
{
	int err;
	struct xfrm_policy_afinfo *afinfo = xfrm_policy_get_afinfo(family);

	if (unlikely(afinfo == NULL))
		return -EINVAL;
	err = afinfo->get_saddr(net, local, remote);
	xfrm_policy_put_afinfo(afinfo);
	return err;
}