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
struct TYPE_2__ {scalar_t__ current_rt_cache_rebuild_count; scalar_t__ sysctl_rt_cache_rebuild_count; } ;
struct net {TYPE_1__ ipv4; } ;

/* Variables and functions */

__attribute__((used)) static inline bool rt_caching(const struct net *net)
{
	return net->ipv4.current_rt_cache_rebuild_count <=
		net->ipv4.sysctl_rt_cache_rebuild_count;
}