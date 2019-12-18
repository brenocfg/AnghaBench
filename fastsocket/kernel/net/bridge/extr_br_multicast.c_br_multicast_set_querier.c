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
struct net_bridge {unsigned long multicast_querier; int /*<<< orphan*/  multicast_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  br_multicast_start_querier (struct net_bridge*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int br_multicast_set_querier(struct net_bridge *br, unsigned long val)
{
	val = !!val;

	spin_lock_bh(&br->multicast_lock);
	if (br->multicast_querier == val)
		goto unlock;

	br->multicast_querier = val;
	if (val)
		br_multicast_start_querier(br);

unlock:
	spin_unlock_bh(&br->multicast_lock);

	return 0;
}