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
struct smsc9420_pdata {int dummy; } ;
struct net_device {int dummy; } ;
struct ethtool_eeprom {int len; size_t offset; int /*<<< orphan*/  magic; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMSC9420_EEPROM_MAGIC ; 
 int SMSC9420_EEPROM_SIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int min (int,int) ; 
 struct smsc9420_pdata* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  smsc9420_eeprom_enable_access (struct smsc9420_pdata*) ; 
 int smsc9420_eeprom_read_location (struct smsc9420_pdata*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int smsc9420_ethtool_get_eeprom(struct net_device *dev,
				       struct ethtool_eeprom *eeprom, u8 *data)
{
	struct smsc9420_pdata *pd = netdev_priv(dev);
	u8 eeprom_data[SMSC9420_EEPROM_SIZE];
	int len, i;

	smsc9420_eeprom_enable_access(pd);

	len = min(eeprom->len, SMSC9420_EEPROM_SIZE);
	for (i = 0; i < len; i++) {
		int ret = smsc9420_eeprom_read_location(pd, i, eeprom_data);
		if (ret < 0) {
			eeprom->len = 0;
			return ret;
		}
	}

	memcpy(data, &eeprom_data[eeprom->offset], len);
	eeprom->magic = SMSC9420_EEPROM_MAGIC;
	eeprom->len = len;
	return 0;
}