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
struct sockaddr_in6 {scalar_t__ sin6_scope_id; } ;
struct rtentry {int dummy; } ;
struct TYPE_2__ {scalar_t__ sa_family; } ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 TYPE_1__* rt_key (struct rtentry*) ; 

void
rtkey_to_sa6(struct rtentry *rt, struct sockaddr_in6 *sin6)
{
	VERIFY(rt_key(rt)->sa_family == AF_INET6);

	*sin6 = *((struct sockaddr_in6 *)(void *)rt_key(rt));
	sin6->sin6_scope_id = 0;
}