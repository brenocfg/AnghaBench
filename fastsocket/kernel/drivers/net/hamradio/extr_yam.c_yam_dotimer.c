#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_3__ {scalar_t__ expires; } ;

/* Variables and functions */
 int HZ ; 
 int NR_PORTS ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 scalar_t__ jiffies ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  yam_arbitrate (struct net_device*) ; 
 struct net_device** yam_devs ; 
 TYPE_1__ yam_timer ; 

__attribute__((used)) static void yam_dotimer(unsigned long dummy)
{
	int i;

	for (i = 0; i < NR_PORTS; i++) {
		struct net_device *dev = yam_devs[i];
		if (dev && netif_running(dev))
			yam_arbitrate(dev);
	}
	yam_timer.expires = jiffies + HZ / 100;
	add_timer(&yam_timer);
}