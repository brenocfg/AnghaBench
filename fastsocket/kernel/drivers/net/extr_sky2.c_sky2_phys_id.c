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
typedef  unsigned int u32 ;
struct sky2_port {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MO_LED_NORM ; 
 int /*<<< orphan*/  MO_LED_OFF ; 
 int /*<<< orphan*/  MO_LED_ON ; 
 unsigned int UINT_MAX ; 
 scalar_t__ msleep_interruptible (int) ; 
 struct sky2_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  sky2_led (struct sky2_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sky2_phys_id(struct net_device *dev, u32 data)
{
	struct sky2_port *sky2 = netdev_priv(dev);
	unsigned int i;

	if (data == 0)
		data = UINT_MAX;

	for (i = 0; i < data; i++) {
		sky2_led(sky2, MO_LED_ON);
		if (msleep_interruptible(500))
			break;
		sky2_led(sky2, MO_LED_OFF);
		if (msleep_interruptible(500))
			break;
	}
	sky2_led(sky2, MO_LED_NORM);

	return 0;
}