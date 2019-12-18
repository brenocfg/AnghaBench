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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct xfrm_policy {int dummy; } ;
struct net {int dummy; } ;
struct flowi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFRM_POLICY_TYPE_MAIN ; 
 int /*<<< orphan*/  XFRM_POLICY_TYPE_SUB ; 
 struct xfrm_policy* xfrm_policy_lookup_bytype (struct net*,int /*<<< orphan*/ ,struct flowi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct xfrm_policy *
__xfrm_policy_lookup(struct net *net, struct flowi *fl, u16 family, u8 dir)
{
#ifdef CONFIG_XFRM_SUB_POLICY
	struct xfrm_policy *pol;

	pol = xfrm_policy_lookup_bytype(net, XFRM_POLICY_TYPE_SUB, fl, family, dir);
	if (pol != NULL)
		return pol;
#endif
	return xfrm_policy_lookup_bytype(net, XFRM_POLICY_TYPE_MAIN, fl, family, dir);
}