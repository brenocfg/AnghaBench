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
struct net_bridge {unsigned long forward_delay; unsigned long bridge_forward_delay; } ;

/* Variables and functions */
 scalar_t__ br_is_root_bridge (struct net_bridge*) ; 
 unsigned long clock_t_to_jiffies (unsigned long) ; 

__attribute__((used)) static int set_forward_delay(struct net_bridge *br, unsigned long val)
{
	unsigned long delay = clock_t_to_jiffies(val);
	br->forward_delay = delay;
	if (br_is_root_bridge(br))
		br->bridge_forward_delay = delay;
	return 0;
}