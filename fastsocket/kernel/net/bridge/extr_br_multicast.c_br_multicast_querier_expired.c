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
struct net_bridge {int /*<<< orphan*/  multicast_lock; scalar_t__ multicast_disabled; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  br_multicast_start_querier (struct net_bridge*) ; 
 int /*<<< orphan*/  netif_running (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void br_multicast_querier_expired(unsigned long data)
{
	struct net_bridge *br = (void *)data;

	spin_lock(&br->multicast_lock);
	if (!netif_running(br->dev) || br->multicast_disabled)
		goto out;

	br_multicast_start_querier(br);

out:
	spin_unlock(&br->multicast_lock);
}