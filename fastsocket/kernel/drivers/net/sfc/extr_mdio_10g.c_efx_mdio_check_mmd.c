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
struct efx_nic {int /*<<< orphan*/  net_dev; } ;

/* Variables and functions */
 int EIO ; 
 int MDIO_MMD_AN ; 
 int /*<<< orphan*/  MDIO_STAT2 ; 
 int MDIO_STAT2_DEVPRST ; 
 int MDIO_STAT2_DEVPRST_VAL ; 
 int efx_mdio_read (struct efx_nic*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw ; 
 int /*<<< orphan*/  netif_err (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int efx_mdio_check_mmd(struct efx_nic *efx, int mmd)
{
	int status;

	if (mmd != MDIO_MMD_AN) {
		/* Read MMD STATUS2 to check it is responding. */
		status = efx_mdio_read(efx, mmd, MDIO_STAT2);
		if ((status & MDIO_STAT2_DEVPRST) != MDIO_STAT2_DEVPRST_VAL) {
			netif_err(efx, hw, efx->net_dev,
				  "PHY MMD %d not responding.\n", mmd);
			return -EIO;
		}
	}

	return 0;
}