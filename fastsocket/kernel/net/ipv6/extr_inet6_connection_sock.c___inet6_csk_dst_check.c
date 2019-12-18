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
typedef  int /*<<< orphan*/  u32 ;
struct sock {int /*<<< orphan*/ * sk_dst_cache; } ;
struct rt6_info {scalar_t__ rt6i_flow_cache_genid; } ;
struct dst_entry {int dummy; } ;

/* Variables and functions */
 struct dst_entry* __sk_dst_check (struct sock*,int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dst_release (struct dst_entry*) ; 
 int /*<<< orphan*/  flow_cache_genid ; 

__attribute__((used)) static inline
struct dst_entry *__inet6_csk_dst_check(struct sock *sk, u32 cookie)
{
	struct dst_entry *dst;

	dst = __sk_dst_check(sk, cookie);

#ifdef CONFIG_XFRM
	if (dst) {
		struct rt6_info *rt = (struct rt6_info *)dst;
		if (rt->rt6i_flow_cache_genid != atomic_read(&flow_cache_genid)) {
			sk->sk_dst_cache = NULL;
			dst_release(dst);
			dst = NULL;
		}
	}
#endif

	return dst;
}