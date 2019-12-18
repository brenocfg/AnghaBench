#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  expires; } ;
struct TYPE_4__ {TYPE_2__ rt_secret_timer; } ;
struct net {TYPE_1__ ipv4; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_timer (TYPE_2__*) ; 
 int /*<<< orphan*/  del_timer_sync (TYPE_2__*) ; 
 scalar_t__ ip_rt_secret_interval ; 
 int /*<<< orphan*/  rt_cache_invalidate (struct net*) ; 

__attribute__((used)) static void rt_secret_rebuild_oneshot(struct net *net)
{
	del_timer_sync(&net->ipv4.rt_secret_timer);
	rt_cache_invalidate(net);
	if (ip_rt_secret_interval) {
		net->ipv4.rt_secret_timer.expires += ip_rt_secret_interval;
		add_timer(&net->ipv4.rt_secret_timer);
	}
}