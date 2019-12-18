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
union nf_inet_addr {int ip; int* ip6; } ;
typedef  scalar_t__ u_int8_t ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int*) ; 
 scalar_t__ NFPROTO_IPV4 ; 
 scalar_t__ memcmp (int**,int**,int) ; 

__attribute__((used)) static inline unsigned int
same_source_net(const union nf_inet_addr *addr,
		const union nf_inet_addr *mask,
		const union nf_inet_addr *u3, u_int8_t family)
{
	if (family == NFPROTO_IPV4) {
		return (addr->ip & mask->ip) == (u3->ip & mask->ip);
	} else {
		union nf_inet_addr lh, rh;
		unsigned int i;

		for (i = 0; i < ARRAY_SIZE(addr->ip6); ++i) {
			lh.ip6[i] = addr->ip6[i] & mask->ip6[i];
			rh.ip6[i] = u3->ip6[i] & mask->ip6[i];
		}

		return memcmp(&lh.ip6, &rh.ip6, sizeof(lh.ip6)) == 0;
	}
}