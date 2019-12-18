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
struct net_device {int dummy; } ;
struct ethtool_drvinfo {int const member_0; int /*<<< orphan*/  version; int /*<<< orphan*/  driver; } ;
typedef  int /*<<< orphan*/  info ;
typedef  int /*<<< orphan*/  ethcmd ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_NAME ; 
 int /*<<< orphan*/  DEVICE_VERSION ; 
 int EFAULT ; 
 int EOPNOTSUPP ; 
#define  ETHTOOL_GDRVINFO 128 
 scalar_t__ copy_from_user (int*,void*,int) ; 
 int /*<<< orphan*/  copy_to_user (void*,struct ethtool_drvinfo*,int) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ethtool_ioctl(struct net_device *dev, void *useraddr)
{
	u32 ethcmd;

	if (copy_from_user(&ethcmd, useraddr, sizeof(ethcmd)))
		return -EFAULT;

        switch (ethcmd) {
	case ETHTOOL_GDRVINFO: {
		struct ethtool_drvinfo info = {ETHTOOL_GDRVINFO};
		strncpy(info.driver, DEVICE_NAME, sizeof(info.driver)-1);
		strncpy(info.version, DEVICE_VERSION, sizeof(info.version)-1);
		if (copy_to_user(useraddr, &info, sizeof(info)))
			return -EFAULT;
		return 0;
	}

        }

	return -EOPNOTSUPP;
}