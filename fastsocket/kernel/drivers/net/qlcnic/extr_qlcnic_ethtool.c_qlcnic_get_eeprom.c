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
typedef  int /*<<< orphan*/  u8 ;
struct qlcnic_adapter {TYPE_1__* pdev; } ;
struct net_device {int dummy; } ;
struct ethtool_eeprom {int magic; int offset; int /*<<< orphan*/  len; } ;
struct TYPE_2__ {int vendor; int device; } ;

/* Variables and functions */
 int EINVAL ; 
 struct qlcnic_adapter* netdev_priv (struct net_device*) ; 
 scalar_t__ qlcnic_82xx_check (struct qlcnic_adapter*) ; 
 scalar_t__ qlcnic_83xx_check (struct qlcnic_adapter*) ; 
 int qlcnic_rom_fast_read_words (struct qlcnic_adapter*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
qlcnic_get_eeprom(struct net_device *dev, struct ethtool_eeprom *eeprom,
		      u8 *bytes)
{
	struct qlcnic_adapter *adapter = netdev_priv(dev);
	int offset;
	int ret = -1;

	if (qlcnic_83xx_check(adapter))
		return 0;
	if (eeprom->len == 0)
		return -EINVAL;

	eeprom->magic = (adapter->pdev)->vendor |
			((adapter->pdev)->device << 16);
	offset = eeprom->offset;

	if (qlcnic_82xx_check(adapter))
		ret = qlcnic_rom_fast_read_words(adapter, offset, bytes,
						 eeprom->len);
	if (ret < 0)
		return ret;

	return 0;
}