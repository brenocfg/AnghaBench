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
struct ip6_msource {int /*<<< orphan*/  im6s_addr; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 int memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static __inline int
ip6_msource_cmp(const struct ip6_msource *a, const struct ip6_msource *b)
{
	return (memcmp(&a->im6s_addr, &b->im6s_addr, sizeof(struct in6_addr)));
}