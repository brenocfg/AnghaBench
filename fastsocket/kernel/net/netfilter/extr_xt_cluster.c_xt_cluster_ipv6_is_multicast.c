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
struct in6_addr {int* s6_addr32; } ;
typedef  int __be32 ;

/* Variables and functions */
 int htonl (int) ; 

__attribute__((used)) static inline bool
xt_cluster_ipv6_is_multicast(const struct in6_addr *addr)
{
	__be32 st = addr->s6_addr32[0];
	return ((st & htonl(0xFF000000)) == htonl(0xFF000000));
}