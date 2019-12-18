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
struct usbnet {int dummy; } ;
struct net_device {int dummy; } ;
struct ethtool_eeprom {int len; scalar_t__ offset; int /*<<< orphan*/  magic; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  AX_CMD_READ_EEPROM ; 
 int /*<<< orphan*/  AX_EEPROM_MAGIC ; 
 int EINVAL ; 
 scalar_t__ asix_read_cmd (struct usbnet*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 struct usbnet* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int asix_get_eeprom(struct net_device *net,
			      struct ethtool_eeprom *eeprom, u8 *data)
{
	struct usbnet *dev = netdev_priv(net);
	__le16 *ebuf = (__le16 *)data;
	int i;

	/* Crude hack to ensure that we don't overwrite memory
	 * if an odd length is supplied
	 */
	if (eeprom->len % 2)
		return -EINVAL;

	eeprom->magic = AX_EEPROM_MAGIC;

	/* ax8817x returns 2 bytes from eeprom on read */
	for (i=0; i < eeprom->len / 2; i++) {
		if (asix_read_cmd(dev, AX_CMD_READ_EEPROM,
			eeprom->offset + i, 0, 2, &ebuf[i]) < 0)
			return -EINVAL;
	}
	return 0;
}