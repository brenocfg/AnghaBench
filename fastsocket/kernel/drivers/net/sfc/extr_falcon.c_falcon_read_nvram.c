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
struct falcon_nvconfig {int /*<<< orphan*/  board_magic_num; int /*<<< orphan*/  board_struct_ver; } ;
struct efx_spi_device {int dummy; } ;
struct falcon_nic_data {struct efx_spi_device spi_flash; int /*<<< orphan*/  spi_lock; struct efx_spi_device spi_eeprom; } ;
struct efx_nic {int /*<<< orphan*/  net_dev; struct falcon_nic_data* nic_data; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int FALCON_NVCONFIG_BOARD_MAGIC_NUM ; 
 int FALCON_NVCONFIG_END ; 
 int FALCON_NVCONFIG_OFFSET ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ efx_spi_present (struct efx_spi_device*) ; 
 int falcon_spi_read (struct efx_nic*,struct efx_spi_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  hw ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct falcon_nvconfig*,struct falcon_nvconfig*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_err (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int
falcon_read_nvram(struct efx_nic *efx, struct falcon_nvconfig *nvconfig_out)
{
	struct falcon_nic_data *nic_data = efx->nic_data;
	struct falcon_nvconfig *nvconfig;
	struct efx_spi_device *spi;
	void *region;
	int rc, magic_num, struct_ver;
	__le16 *word, *limit;
	u32 csum;

	if (efx_spi_present(&nic_data->spi_flash))
		spi = &nic_data->spi_flash;
	else if (efx_spi_present(&nic_data->spi_eeprom))
		spi = &nic_data->spi_eeprom;
	else
		return -EINVAL;

	region = kmalloc(FALCON_NVCONFIG_END, GFP_KERNEL);
	if (!region)
		return -ENOMEM;
	nvconfig = region + FALCON_NVCONFIG_OFFSET;

	mutex_lock(&nic_data->spi_lock);
	rc = falcon_spi_read(efx, spi, 0, FALCON_NVCONFIG_END, NULL, region);
	mutex_unlock(&nic_data->spi_lock);
	if (rc) {
		netif_err(efx, hw, efx->net_dev, "Failed to read %s\n",
			  efx_spi_present(&nic_data->spi_flash) ?
			  "flash" : "EEPROM");
		rc = -EIO;
		goto out;
	}

	magic_num = le16_to_cpu(nvconfig->board_magic_num);
	struct_ver = le16_to_cpu(nvconfig->board_struct_ver);

	rc = -EINVAL;
	if (magic_num != FALCON_NVCONFIG_BOARD_MAGIC_NUM) {
		netif_err(efx, hw, efx->net_dev,
			  "NVRAM bad magic 0x%x\n", magic_num);
		goto out;
	}
	if (struct_ver < 2) {
		netif_err(efx, hw, efx->net_dev,
			  "NVRAM has ancient version 0x%x\n", struct_ver);
		goto out;
	} else if (struct_ver < 4) {
		word = &nvconfig->board_magic_num;
		limit = (__le16 *) (nvconfig + 1);
	} else {
		word = region;
		limit = region + FALCON_NVCONFIG_END;
	}
	for (csum = 0; word < limit; ++word)
		csum += le16_to_cpu(*word);

	if (~csum & 0xffff) {
		netif_err(efx, hw, efx->net_dev,
			  "NVRAM has incorrect checksum\n");
		goto out;
	}

	rc = 0;
	if (nvconfig_out)
		memcpy(nvconfig_out, nvconfig, sizeof(*nvconfig));

 out:
	kfree(region);
	return rc;
}