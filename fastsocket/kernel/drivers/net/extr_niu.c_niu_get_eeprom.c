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
typedef  scalar_t__ u32 ;
struct niu {scalar_t__ eeprom_len; } ;
struct net_device {int dummy; } ;
struct ethtool_eeprom {scalar_t__ offset; scalar_t__ len; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ESPC_NCR (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,...) ; 
 struct niu* netdev_priv (struct net_device*) ; 
 scalar_t__ nr64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int niu_get_eeprom(struct net_device *dev,
			  struct ethtool_eeprom *eeprom, u8 *data)
{
	struct niu *np = netdev_priv(dev);
	u32 offset, len, val;

	offset = eeprom->offset;
	len = eeprom->len;

	if (offset + len < offset)
		return -EINVAL;
	if (offset >= np->eeprom_len)
		return -EINVAL;
	if (offset + len > np->eeprom_len)
		len = eeprom->len = np->eeprom_len - offset;

	if (offset & 3) {
		u32 b_offset, b_count;

		b_offset = offset & 3;
		b_count = 4 - b_offset;
		if (b_count > len)
			b_count = len;

		val = nr64(ESPC_NCR((offset - b_offset) / 4));
		memcpy(data, ((char *)&val) + b_offset, b_count);
		data += b_count;
		len -= b_count;
		offset += b_count;
	}
	while (len >= 4) {
		val = nr64(ESPC_NCR(offset / 4));
		memcpy(data, &val, 4);
		data += 4;
		len -= 4;
		offset += 4;
	}
	if (len) {
		val = nr64(ESPC_NCR(offset / 4));
		memcpy(data, &val, len);
	}
	return 0;
}