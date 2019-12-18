#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rt6_info {int rt6i_flags; } ;
struct TYPE_3__ {scalar_t__ ip6_rt_gc_interval; } ;
struct TYPE_4__ {TYPE_1__ sysctl; int /*<<< orphan*/  ip6_fib_timer; } ;
struct net {TYPE_2__ ipv6; } ;

/* Variables and functions */
 int RTF_CACHE ; 
 int RTF_EXPIRES ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  timer_pending (int /*<<< orphan*/ *) ; 

__attribute__((used)) static __inline__ void fib6_start_gc(struct net *net, struct rt6_info *rt)
{
	if (!timer_pending(&net->ipv6.ip6_fib_timer) &&
	    (rt->rt6i_flags & (RTF_EXPIRES|RTF_CACHE)))
		mod_timer(&net->ipv6.ip6_fib_timer,
			  jiffies + net->ipv6.sysctl.ip6_rt_gc_interval);
}