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
struct adapter {int dummy; } ;
typedef  int /*<<< orphan*/  csum ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  CH_ERR (struct adapter*,char*,int) ; 
 int EFBIG ; 
 int EINVAL ; 
 int FW_FLASH_BOOT_ADDR ; 
 unsigned int FW_MIN_SIZE ; 
 int FW_VERS_ADDR ; 
 unsigned int min (unsigned int,unsigned int) ; 
 scalar_t__ ntohl (int /*<<< orphan*/  const) ; 
 int t3_flash_erase_sectors (struct adapter*,int,int) ; 
 int t3_write_flash (struct adapter*,int,int,int /*<<< orphan*/  const*) ; 

int t3_load_fw(struct adapter *adapter, const u8 *fw_data, unsigned int size)
{
	u32 csum;
	unsigned int i;
	const __be32 *p = (const __be32 *)fw_data;
	int ret, addr, fw_sector = FW_FLASH_BOOT_ADDR >> 16;

	if ((size & 3) || size < FW_MIN_SIZE)
		return -EINVAL;
	if (size > FW_VERS_ADDR + 8 - FW_FLASH_BOOT_ADDR)
		return -EFBIG;

	for (csum = 0, i = 0; i < size / sizeof(csum); i++)
		csum += ntohl(p[i]);
	if (csum != 0xffffffff) {
		CH_ERR(adapter, "corrupted firmware image, checksum %u\n",
		       csum);
		return -EINVAL;
	}

	ret = t3_flash_erase_sectors(adapter, fw_sector, fw_sector);
	if (ret)
		goto out;

	size -= 8;		/* trim off version and checksum */
	for (addr = FW_FLASH_BOOT_ADDR; size;) {
		unsigned int chunk_size = min(size, 256U);

		ret = t3_write_flash(adapter, addr, chunk_size, fw_data);
		if (ret)
			goto out;

		addr += chunk_size;
		fw_data += chunk_size;
		size -= chunk_size;
	}

	ret = t3_write_flash(adapter, FW_VERS_ADDR, 4, fw_data);
out:
	if (ret)
		CH_ERR(adapter, "firmware download failed, error %d\n", ret);
	return ret;
}