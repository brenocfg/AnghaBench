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
typedef  int u32 ;
struct net_device {int dummy; } ;
struct ethtool_eeprom {scalar_t__ magic; int offset; int len; } ;
struct adapter {int fn; } ;

/* Variables and functions */
 int EEPROMPFSIZE ; 
 scalar_t__ EEPROM_MAGIC ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EPERM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int eeprom_rd_phys (struct adapter*,int,int*) ; 
 int eeprom_wr_phys (struct adapter*,int,int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct adapter* netdev2adap (struct net_device*) ; 
 int t4_seeprom_wp (struct adapter*,int) ; 

__attribute__((used)) static int set_eeprom(struct net_device *dev, struct ethtool_eeprom *eeprom,
		      u8 *data)
{
	u8 *buf;
	int err = 0;
	u32 aligned_offset, aligned_len, *p;
	struct adapter *adapter = netdev2adap(dev);

	if (eeprom->magic != EEPROM_MAGIC)
		return -EINVAL;

	aligned_offset = eeprom->offset & ~3;
	aligned_len = (eeprom->len + (eeprom->offset & 3) + 3) & ~3;

	if (adapter->fn > 0) {
		u32 start = 1024 + adapter->fn * EEPROMPFSIZE;

		if (aligned_offset < start ||
		    aligned_offset + aligned_len > start + EEPROMPFSIZE)
			return -EPERM;
	}

	if (aligned_offset != eeprom->offset || aligned_len != eeprom->len) {
		/*
		 * RMW possibly needed for first or last words.
		 */
		buf = kmalloc(aligned_len, GFP_KERNEL);
		if (!buf)
			return -ENOMEM;
		err = eeprom_rd_phys(adapter, aligned_offset, (u32 *)buf);
		if (!err && aligned_len > 4)
			err = eeprom_rd_phys(adapter,
					     aligned_offset + aligned_len - 4,
					     (u32 *)&buf[aligned_len - 4]);
		if (err)
			goto out;
		memcpy(buf + (eeprom->offset & 3), data, eeprom->len);
	} else
		buf = data;

	err = t4_seeprom_wp(adapter, false);
	if (err)
		goto out;

	for (p = (u32 *)buf; !err && aligned_len; aligned_len -= 4, p++) {
		err = eeprom_wr_phys(adapter, aligned_offset, *p);
		aligned_offset += 4;
	}

	if (!err)
		err = t4_seeprom_wp(adapter, true);
out:
	if (buf != data)
		kfree(buf);
	return err;
}