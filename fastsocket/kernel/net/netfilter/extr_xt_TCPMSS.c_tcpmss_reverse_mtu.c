#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u_int32_t ;
struct sk_buff {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  dst; } ;
struct rtable {TYPE_1__ u; } ;
struct nf_afinfo {int /*<<< orphan*/  (* route ) (struct dst_entry**,struct flowi*) ;} ;
struct flowi {int /*<<< orphan*/  fl6_dst; int /*<<< orphan*/  fl4_dst; } ;
struct dst_entry {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  saddr; } ;
struct TYPE_5__ {int /*<<< orphan*/  saddr; } ;

/* Variables and functions */
 unsigned int PF_INET ; 
 unsigned int dst_mtu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dst_release (int /*<<< orphan*/ *) ; 
 TYPE_3__* ip_hdr (struct sk_buff const*) ; 
 TYPE_2__* ipv6_hdr (struct sk_buff const*) ; 
 struct nf_afinfo* nf_get_afinfo (unsigned int) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  stub1 (struct dst_entry**,struct flowi*) ; 

__attribute__((used)) static u_int32_t tcpmss_reverse_mtu(const struct sk_buff *skb,
				    unsigned int family)
{
	struct flowi fl = {};
	const struct nf_afinfo *ai;
	struct rtable *rt = NULL;
	u_int32_t mtu     = ~0U;

	if (family == PF_INET)
		fl.fl4_dst = ip_hdr(skb)->saddr;
	else
		fl.fl6_dst = ipv6_hdr(skb)->saddr;

	rcu_read_lock();
	ai = nf_get_afinfo(family);
	if (ai != NULL)
		ai->route((struct dst_entry **)&rt, &fl);
	rcu_read_unlock();

	if (rt != NULL) {
		mtu = dst_mtu(&rt->u.dst);
		dst_release(&rt->u.dst);
	}
	return mtu;
}