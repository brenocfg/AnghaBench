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
struct TYPE_2__ {int /*<<< orphan*/  rt_secret_timer; } ;
struct net {TYPE_1__ ipv4; } ;

/* Variables and functions */
 scalar_t__ ip_rt_secret_interval ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  rt_cache_invalidate (struct net*) ; 

__attribute__((used)) static void rt_secret_rebuild(unsigned long __net)
{
	struct net *net = (struct net *)__net;
	rt_cache_invalidate(net);
	mod_timer(&net->ipv4.rt_secret_timer, jiffies + ip_rt_secret_interval);
}