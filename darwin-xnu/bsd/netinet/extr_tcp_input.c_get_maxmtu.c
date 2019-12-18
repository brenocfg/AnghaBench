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
struct rtentry {int dummy; } ;
struct TYPE_2__ {scalar_t__ sa_family; } ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  RT_LOCK (struct rtentry*) ; 
 int /*<<< orphan*/  RT_LOCK_ASSERT_NOTHELD (struct rtentry*) ; 
 int /*<<< orphan*/  RT_UNLOCK (struct rtentry*) ; 
 TYPE_1__* rt_key (struct rtentry*) ; 
 unsigned int tcp_maxmtu (struct rtentry*) ; 
 unsigned int tcp_maxmtu6 (struct rtentry*) ; 

unsigned int
get_maxmtu(struct rtentry *rt)
{
	unsigned int maxmtu = 0;

	RT_LOCK_ASSERT_NOTHELD(rt);

	RT_LOCK(rt);

	if (rt_key(rt)->sa_family == AF_INET6) {
		maxmtu = tcp_maxmtu6(rt);
	} else {
		maxmtu = tcp_maxmtu(rt);
	}

	RT_UNLOCK(rt);

	return (maxmtu);
}