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
typedef  int u32 ;
struct skge_port {int dummy; } ;
struct net_device {int dummy; } ;
typedef  enum led_mode { ____Placeholder_led_mode } led_mode ;

/* Variables and functions */
 scalar_t__ BLINK_MS ; 
 int HZ ; 
 int LED_MODE_OFF ; 
 int LED_MODE_ON ; 
 int LED_MODE_TST ; 
 int MAX_SCHEDULE_TIMEOUT ; 
 int jiffies_to_msecs (int) ; 
 scalar_t__ msleep_interruptible (scalar_t__) ; 
 struct skge_port* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  skge_led (struct skge_port*,int) ; 

__attribute__((used)) static int skge_phys_id(struct net_device *dev, u32 data)
{
	struct skge_port *skge = netdev_priv(dev);
	unsigned long ms;
	enum led_mode mode = LED_MODE_TST;

	if (!data || data > (u32)(MAX_SCHEDULE_TIMEOUT / HZ))
		ms = jiffies_to_msecs(MAX_SCHEDULE_TIMEOUT / HZ) * 1000;
	else
		ms = data * 1000;

	while (ms > 0) {
		skge_led(skge, mode);
		mode ^= LED_MODE_TST;

		if (msleep_interruptible(BLINK_MS))
			break;
		ms -= BLINK_MS;
	}

	/* back to regular LED state */
	skge_led(skge, netif_running(dev) ? LED_MODE_ON : LED_MODE_OFF);

	return 0;
}