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
struct in6_addr {int /*<<< orphan*/ * s6_addr32; } ;

/* Variables and functions */
 int hash_ip (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int hash_ip6(struct in6_addr ip)
{
	return (hash_ip(ip.s6_addr32[0]) ^
		hash_ip(ip.s6_addr32[1]) ^
		hash_ip(ip.s6_addr32[2]) ^
		hash_ip(ip.s6_addr32[3]));
}