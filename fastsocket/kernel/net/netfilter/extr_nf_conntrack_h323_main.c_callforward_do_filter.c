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
union nf_inet_addr {int /*<<< orphan*/  ip; } ;
typedef  int u_int8_t ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {TYPE_3__ dst; } ;
struct rtable {TYPE_1__ u; int /*<<< orphan*/  rt_gateway; } ;
struct TYPE_5__ {TYPE_3__ dst; } ;
struct rt6_info {TYPE_2__ u; int /*<<< orphan*/  rt6i_gateway; } ;
struct nf_afinfo {int /*<<< orphan*/  (* route ) (struct dst_entry**,struct flowi*) ;} ;
struct flowi {int /*<<< orphan*/  fl6_dst; int /*<<< orphan*/  fl4_dst; } ;
struct dst_entry {int dummy; } ;
typedef  int /*<<< orphan*/  fl2 ;
typedef  int /*<<< orphan*/  fl1 ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  dst_release (TYPE_3__*) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,union nf_inet_addr const*,int) ; 
 int /*<<< orphan*/  memset (struct flowi*,int /*<<< orphan*/ ,int) ; 
 struct nf_afinfo* nf_get_afinfo (int) ; 
 int /*<<< orphan*/  stub1 (struct dst_entry**,struct flowi*) ; 
 int /*<<< orphan*/  stub2 (struct dst_entry**,struct flowi*) ; 
 int /*<<< orphan*/  stub3 (struct dst_entry**,struct flowi*) ; 
 int /*<<< orphan*/  stub4 (struct dst_entry**,struct flowi*) ; 

__attribute__((used)) static int callforward_do_filter(const union nf_inet_addr *src,
				 const union nf_inet_addr *dst,
				 u_int8_t family)
{
	const struct nf_afinfo *afinfo;
	struct flowi fl1, fl2;
	int ret = 0;

	/* rcu_read_lock()ed by nf_hook_slow() */
	afinfo = nf_get_afinfo(family);
	if (!afinfo)
		return 0;

	memset(&fl1, 0, sizeof(fl1));
	memset(&fl2, 0, sizeof(fl2));

	switch (family) {
	case AF_INET: {
		struct rtable *rt1, *rt2;

		fl1.fl4_dst = src->ip;
		fl2.fl4_dst = dst->ip;
		if (!afinfo->route((struct dst_entry **)&rt1, &fl1)) {
			if (!afinfo->route((struct dst_entry **)&rt2, &fl2)) {
				if (rt1->rt_gateway == rt2->rt_gateway &&
				    rt1->u.dst.dev  == rt2->u.dst.dev)
					ret = 1;
				dst_release(&rt2->u.dst);
			}
			dst_release(&rt1->u.dst);
		}
		break;
	}
#if defined(CONFIG_NF_CONNTRACK_IPV6) || \
    defined(CONFIG_NF_CONNTRACK_IPV6_MODULE)
	case AF_INET6: {
		struct rt6_info *rt1, *rt2;

		memcpy(&fl1.fl6_dst, src, sizeof(fl1.fl6_dst));
		memcpy(&fl2.fl6_dst, dst, sizeof(fl2.fl6_dst));
		if (!afinfo->route((struct dst_entry **)&rt1, &fl1)) {
			if (!afinfo->route((struct dst_entry **)&rt2, &fl2)) {
				if (!memcmp(&rt1->rt6i_gateway, &rt2->rt6i_gateway,
					    sizeof(rt1->rt6i_gateway)) &&
				    rt1->u.dst.dev == rt2->u.dst.dev)
					ret = 1;
				dst_release(&rt2->u.dst);
			}
			dst_release(&rt1->u.dst);
		}
		break;
	}
#endif
	}
	return ret;

}