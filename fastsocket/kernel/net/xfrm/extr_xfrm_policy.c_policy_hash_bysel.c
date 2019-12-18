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
struct xfrm_selector {int dummy; } ;
struct TYPE_4__ {TYPE_1__* policy_bydst; struct hlist_head* policy_inexact; } ;
struct net {TYPE_2__ xfrm; } ;
struct hlist_head {int dummy; } ;
struct TYPE_3__ {unsigned int hmask; struct hlist_head* table; } ;

/* Variables and functions */
 unsigned int __sel_hash (struct xfrm_selector*,unsigned short,unsigned int) ; 

__attribute__((used)) static struct hlist_head *policy_hash_bysel(struct net *net, struct xfrm_selector *sel, unsigned short family, int dir)
{
	unsigned int hmask = net->xfrm.policy_bydst[dir].hmask;
	unsigned int hash = __sel_hash(sel, family, hmask);

	return (hash == hmask + 1 ?
		&net->xfrm.policy_inexact[dir] :
		net->xfrm.policy_bydst[dir].table + hash);
}