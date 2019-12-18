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
struct net_device {int /*<<< orphan*/  name; TYPE_1__* ethtool_ops; } ;
struct ethtool_cmd {int speed; int /*<<< orphan*/  cmd; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_settings ) (struct net_device*,struct ethtool_cmd*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ETHTOOL_GSET ; 
#define  SPEED_10 131 
#define  SPEED_100 130 
#define  SPEED_1000 129 
#define  SPEED_10000 128 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stub1 (struct net_device*,struct ethtool_cmd*) ; 

__attribute__((used)) static int port_cost(struct net_device *dev)
{
	if (dev->ethtool_ops && dev->ethtool_ops->get_settings) {
		struct ethtool_cmd ecmd = { .cmd = ETHTOOL_GSET, };

		if (!dev->ethtool_ops->get_settings(dev, &ecmd)) {
			switch(ecmd.speed) {
			case SPEED_10000:
				return 2;
			case SPEED_1000:
				return 4;
			case SPEED_100:
				return 19;
			case SPEED_10:
				return 100;
			}
		}
	}

	/* Old silly heuristics based on name */
	if (!strncmp(dev->name, "lec", 3))
		return 7;

	if (!strncmp(dev->name, "plip", 4))
		return 2500;

	return 100;	/* assume old 10Mbps */
}