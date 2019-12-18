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
struct sock {int dummy; } ;
struct rt6_info {int /*<<< orphan*/  rt6i_flow_cache_genid; } ;
struct in6_addr {int dummy; } ;
struct dst_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ip6_dst_store (struct sock*,struct dst_entry*,struct in6_addr*,struct in6_addr*) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flow_cache_genid ; 

__attribute__((used)) static inline
void __inet6_csk_dst_store(struct sock *sk, struct dst_entry *dst,
			   struct in6_addr *daddr, struct in6_addr *saddr)
{
	__ip6_dst_store(sk, dst, daddr, saddr);

#ifdef CONFIG_XFRM
	{
		struct rt6_info *rt = (struct rt6_info  *)dst;
		rt->rt6i_flow_cache_genid = atomic_read(&flow_cache_genid);
	}
#endif
}