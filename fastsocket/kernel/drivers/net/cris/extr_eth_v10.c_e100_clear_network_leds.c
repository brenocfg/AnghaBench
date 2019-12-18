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
struct net_local {int /*<<< orphan*/  led_lock; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ NET_FLASH_PAUSE ; 
 int /*<<< orphan*/  NO_NETWORK_ACTIVITY ; 
 int /*<<< orphan*/  e100_set_network_leds (int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 scalar_t__ led_active ; 
 scalar_t__ led_next_time ; 
 struct net_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
e100_clear_network_leds(unsigned long dummy)
{
	struct net_device *dev = (struct net_device *)dummy;
	struct net_local *np = netdev_priv(dev);

	spin_lock(&np->led_lock);

	if (led_active && time_after(jiffies, led_next_time)) {
		e100_set_network_leds(NO_NETWORK_ACTIVITY);

		/* Set the earliest time we may set the LED */
		led_next_time = jiffies + NET_FLASH_PAUSE;
		led_active = 0;
	}

	spin_unlock(&np->led_lock);
}