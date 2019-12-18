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
struct xfrm_policy_afinfo {struct dst_entry* (* dst_lookup ) (struct net*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
struct net {int dummy; } ;
struct dst_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAFNOSUPPORT ; 
 struct dst_entry* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct dst_entry* stub1 (struct net*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 struct xfrm_policy_afinfo* xfrm_policy_get_afinfo (int) ; 
 int /*<<< orphan*/  xfrm_policy_put_afinfo (struct xfrm_policy_afinfo*) ; 

__attribute__((used)) static inline struct dst_entry *__xfrm_dst_lookup(struct net *net, int tos,
						  xfrm_address_t *saddr,
						  xfrm_address_t *daddr,
						  int family)
{
	struct xfrm_policy_afinfo *afinfo;
	struct dst_entry *dst;

	afinfo = xfrm_policy_get_afinfo(family);
	if (unlikely(afinfo == NULL))
		return ERR_PTR(-EAFNOSUPPORT);

	dst = afinfo->dst_lookup(net, tos, saddr, daddr);

	xfrm_policy_put_afinfo(afinfo);

	return dst;
}