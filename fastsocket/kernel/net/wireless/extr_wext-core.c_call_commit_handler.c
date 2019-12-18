#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct net_device {TYPE_1__* wireless_handlers; } ;
struct TYPE_2__ {int (* standard ) (struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 scalar_t__ netif_running (struct net_device*) ; 
 int stub1 (struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int call_commit_handler(struct net_device *dev)
{
#ifdef CONFIG_WIRELESS_EXT
	if ((netif_running(dev)) &&
	   (dev->wireless_handlers->standard[0] != NULL))
		/* Call the commit handler on the driver */
		return dev->wireless_handlers->standard[0](dev, NULL,
							   NULL, NULL);
	else
		return 0;		/* Command completed successfully */
#else
	/* cfg80211 has no commit */
	return 0;
#endif
}