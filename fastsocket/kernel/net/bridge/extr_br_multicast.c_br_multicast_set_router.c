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
struct net_bridge {unsigned long multicast_router; int /*<<< orphan*/  multicast_lock; int /*<<< orphan*/  multicast_router_timer; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_running (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int br_multicast_set_router(struct net_bridge *br, unsigned long val)
{
	int err = -ENOENT;

	spin_lock_bh(&br->multicast_lock);
	if (!netif_running(br->dev))
		goto unlock;

	switch (val) {
	case 0:
	case 2:
		del_timer(&br->multicast_router_timer);
		/* fall through */
	case 1:
		br->multicast_router = val;
		err = 0;
		break;

	default:
		err = -EINVAL;
		break;
	}

unlock:
	spin_unlock_bh(&br->multicast_lock);

	return err;
}