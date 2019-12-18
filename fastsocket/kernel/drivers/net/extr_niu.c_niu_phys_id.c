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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct niu {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 scalar_t__ msleep_interruptible (int) ; 
 struct niu* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  niu_force_led (struct niu*,int) ; 
 int /*<<< orphan*/  niu_led_state_restore (struct niu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  niu_led_state_save (struct niu*) ; 

__attribute__((used)) static int niu_phys_id(struct net_device *dev, u32 data)
{
	struct niu *np = netdev_priv(dev);
	u64 orig_led_state;
	int i;

	if (!netif_running(dev))
		return -EAGAIN;

	if (data == 0)
		data = 2;

	orig_led_state = niu_led_state_save(np);
	for (i = 0; i < (data * 2); i++) {
		int on = ((i % 2) == 0);

		niu_force_led(np, on);

		if (msleep_interruptible(500))
			break;
	}
	niu_led_state_restore(np, orig_led_state);

	return 0;
}