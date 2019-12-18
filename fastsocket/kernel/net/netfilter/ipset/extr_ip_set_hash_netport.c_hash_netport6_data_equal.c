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
struct TYPE_2__ {int /*<<< orphan*/  in6; } ;
struct hash_netport6_elem {scalar_t__ port; scalar_t__ proto; scalar_t__ cidr; TYPE_1__ ip; } ;

/* Variables and functions */
 scalar_t__ ipv6_addr_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool
hash_netport6_data_equal(const struct hash_netport6_elem *ip1,
			 const struct hash_netport6_elem *ip2)
{
	return ipv6_addr_cmp(&ip1->ip.in6, &ip2->ip.in6) == 0 &&
	       ip1->port == ip2->port &&
	       ip1->proto == ip2->proto &&
	       ip1->cidr == ip2->cidr;
}