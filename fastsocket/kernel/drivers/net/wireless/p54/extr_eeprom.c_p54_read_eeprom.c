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
struct p54_common {int fw_var; } ;
struct ieee80211_hw {struct p54_common* priv; } ;

/* Variables and functions */
 size_t EEPROM_READBACK_LEN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kzalloc (size_t,int /*<<< orphan*/ ) ; 
 size_t min (size_t,size_t) ; 
 int p54_download_eeprom (struct p54_common*,void*,size_t,size_t) ; 
 int p54_parse_eeprom (struct ieee80211_hw*,void*,size_t) ; 
 scalar_t__ unlikely (int) ; 

int p54_read_eeprom(struct ieee80211_hw *dev)
{
	struct p54_common *priv = dev->priv;
	size_t eeprom_size = 0x2020, offset = 0, blocksize, maxblocksize;
	int ret = -ENOMEM;
	void *eeprom;

	maxblocksize = EEPROM_READBACK_LEN;
	if (priv->fw_var >= 0x509)
		maxblocksize -= 0xc;
	else
		maxblocksize -= 0x4;

	eeprom = kzalloc(eeprom_size, GFP_KERNEL);
	if (unlikely(!eeprom))
		goto free;

	while (eeprom_size) {
		blocksize = min(eeprom_size, maxblocksize);
		ret = p54_download_eeprom(priv, eeprom + offset,
					  offset, blocksize);
		if (unlikely(ret))
			goto free;

		offset += blocksize;
		eeprom_size -= blocksize;
	}

	ret = p54_parse_eeprom(dev, eeprom, offset);
free:
	kfree(eeprom);
	return ret;
}