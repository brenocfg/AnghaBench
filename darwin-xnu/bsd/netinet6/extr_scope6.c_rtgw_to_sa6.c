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
struct sockaddr_in6 {scalar_t__ sin6_scope_id; } ;
struct rtentry {int rt_flags; scalar_t__ rt_gateway; } ;

/* Variables and functions */
 int RTF_GATEWAY ; 
 int /*<<< orphan*/  VERIFY (int) ; 

void
rtgw_to_sa6(struct rtentry *rt, struct sockaddr_in6 *sin6)
{
	VERIFY(rt->rt_flags & RTF_GATEWAY);

	*sin6 = *((struct sockaddr_in6 *)(void *)rt->rt_gateway);
	sin6->sin6_scope_id = 0;
}