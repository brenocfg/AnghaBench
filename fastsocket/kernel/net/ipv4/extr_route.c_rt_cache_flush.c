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
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  in_softirq () ; 
 int /*<<< orphan*/  rt_cache_invalidate (struct net*) ; 
 int /*<<< orphan*/  rt_do_flush (int) ; 

void rt_cache_flush(struct net *net, int delay)
{
	rt_cache_invalidate(net);
	if (delay >= 0)
		rt_do_flush(!in_softirq());
}