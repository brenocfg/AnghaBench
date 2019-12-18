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
typedef  int /*<<< orphan*/  u8 ;
struct net_device {int dummy; } ;
struct jme_adapter {int dummy; } ;
struct ethtool_eeprom {int offset; int len; int /*<<< orphan*/  magic; } ;

/* Variables and functions */
 int /*<<< orphan*/  JME_EEPROM_MAGIC ; 
 int /*<<< orphan*/  jme_smb_read (struct jme_adapter*,int) ; 
 struct jme_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
jme_get_eeprom(struct net_device *netdev,
		struct ethtool_eeprom *eeprom, u8 *data)
{
	struct jme_adapter *jme = netdev_priv(netdev);
	int i, offset = eeprom->offset, len = eeprom->len;

	/*
	 * ethtool will check the boundary for us
	 */
	eeprom->magic = JME_EEPROM_MAGIC;
	for (i = 0 ; i < len ; ++i)
		data[i] = jme_smb_read(jme, i + offset);

	return 0;
}