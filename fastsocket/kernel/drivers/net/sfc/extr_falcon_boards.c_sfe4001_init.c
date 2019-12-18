#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct falcon_board {void* hwmon_client; void* ioexp_client; int /*<<< orphan*/  i2c_adap; } ;
struct efx_nic {int phy_mode; int /*<<< orphan*/  net_dev; TYPE_1__* pci_dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  MAX664X_REG_WLHO ; 
 int /*<<< orphan*/  PCA9539 ; 
 int PHY_MODE_SPECIAL ; 
 int /*<<< orphan*/  dev_attr_phy_flash_cfg ; 
 int device_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct falcon_board* falcon_board (struct efx_nic*) ; 
 int /*<<< orphan*/  falcon_stop_nic_stats (struct efx_nic*) ; 
 int /*<<< orphan*/  hw ; 
 void* i2c_new_device (int /*<<< orphan*/ *,TYPE_2__*) ; 
 void* i2c_new_dummy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int i2c_smbus_write_byte_data (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i2c_unregister_device (void*) ; 
 int /*<<< orphan*/  netif_info (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 TYPE_2__ sfe4001_hwmon_info ; 
 int /*<<< orphan*/  sfe4001_poweroff (struct efx_nic*) ; 
 int sfe4001_poweron (struct efx_nic*) ; 

__attribute__((used)) static int sfe4001_init(struct efx_nic *efx)
{
	struct falcon_board *board = falcon_board(efx);
	int rc;

#if defined(CONFIG_SENSORS_LM90) || defined(CONFIG_SENSORS_LM90_MODULE)
	board->hwmon_client =
		i2c_new_device(&board->i2c_adap, &sfe4001_hwmon_info);
#else
	board->hwmon_client =
		i2c_new_dummy(&board->i2c_adap, sfe4001_hwmon_info.addr);
#endif
	if (!board->hwmon_client)
		return -EIO;

	/* Raise board/PHY high limit from 85 to 90 degrees Celsius */
	rc = i2c_smbus_write_byte_data(board->hwmon_client,
				       MAX664X_REG_WLHO, 90);
	if (rc)
		goto fail_hwmon;

	board->ioexp_client = i2c_new_dummy(&board->i2c_adap, PCA9539);
	if (!board->ioexp_client) {
		rc = -EIO;
		goto fail_hwmon;
	}

	if (efx->phy_mode & PHY_MODE_SPECIAL) {
		/* PHY won't generate a 156.25 MHz clock and MAC stats fetch
		 * will fail. */
		falcon_stop_nic_stats(efx);
	}
	rc = sfe4001_poweron(efx);
	if (rc)
		goto fail_ioexp;

	rc = device_create_file(&efx->pci_dev->dev, &dev_attr_phy_flash_cfg);
	if (rc)
		goto fail_on;

	netif_info(efx, hw, efx->net_dev, "PHY is powered on\n");
	return 0;

fail_on:
	sfe4001_poweroff(efx);
fail_ioexp:
	i2c_unregister_device(board->ioexp_client);
fail_hwmon:
	i2c_unregister_device(board->hwmon_client);
	return rc;
}