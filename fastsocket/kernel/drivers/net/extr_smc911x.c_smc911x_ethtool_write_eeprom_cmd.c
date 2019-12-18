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
struct smc911x_local {int dummy; } ;
struct net_device {int dummy; } ;
typedef  int cmd ;
typedef  int addr ;

/* Variables and functions */
 int E2P_CMD_EPC_BUSY_ ; 
 int /*<<< orphan*/  SMC_SET_E2P_CMD (struct smc911x_local*,int) ; 
 struct smc911x_local* netdev_priv (struct net_device*) ; 
 int smc911x_ethtool_wait_eeprom_ready (struct net_device*) ; 

__attribute__((used)) static inline int smc911x_ethtool_write_eeprom_cmd(struct net_device *dev,
													int cmd, int addr)
{
	struct smc911x_local *lp = netdev_priv(dev);
	int ret;

	if ((ret = smc911x_ethtool_wait_eeprom_ready(dev))!=0)
		return ret;
	SMC_SET_E2P_CMD(lp, E2P_CMD_EPC_BUSY_ |
		((cmd) & (0x7<<28)) |
		((addr) & 0xFF));
	return 0;
}