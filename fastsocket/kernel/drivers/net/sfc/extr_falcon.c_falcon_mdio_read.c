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
typedef  int /*<<< orphan*/  u16 ;
struct net_device {int dummy; } ;
struct falcon_nic_data {int /*<<< orphan*/  mdio_lock; } ;
struct efx_nic {int /*<<< orphan*/  net_dev; struct falcon_nic_data* nic_data; } ;
typedef  int /*<<< orphan*/  efx_oword_t ;

/* Variables and functions */
 int EFX_OWORD_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EFX_POPULATE_OWORD_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EFX_POPULATE_OWORD_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FRF_AB_MD_DEV_ADR ; 
 int /*<<< orphan*/  FRF_AB_MD_GC ; 
 int /*<<< orphan*/  FRF_AB_MD_PHY_ADR ; 
 int /*<<< orphan*/  FRF_AB_MD_PRT_ADR ; 
 int /*<<< orphan*/  FRF_AB_MD_RDC ; 
 int /*<<< orphan*/  FRF_AB_MD_RIC ; 
 int /*<<< orphan*/  FRF_AB_MD_RXD ; 
 int /*<<< orphan*/  FR_AB_MD_CS ; 
 int /*<<< orphan*/  FR_AB_MD_ID ; 
 int /*<<< orphan*/  FR_AB_MD_PHY_ADR ; 
 int /*<<< orphan*/  FR_AB_MD_RXD ; 
 int /*<<< orphan*/  efx_reado (struct efx_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_writeo (struct efx_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int falcon_gmii_wait (struct efx_nic*) ; 
 int /*<<< orphan*/  hw ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct efx_nic* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_dbg (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netif_vdbg (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int falcon_mdio_read(struct net_device *net_dev,
			    int prtad, int devad, u16 addr)
{
	struct efx_nic *efx = netdev_priv(net_dev);
	struct falcon_nic_data *nic_data = efx->nic_data;
	efx_oword_t reg;
	int rc;

	mutex_lock(&nic_data->mdio_lock);

	/* Check MDIO not currently being accessed */
	rc = falcon_gmii_wait(efx);
	if (rc)
		goto out;

	EFX_POPULATE_OWORD_1(reg, FRF_AB_MD_PHY_ADR, addr);
	efx_writeo(efx, &reg, FR_AB_MD_PHY_ADR);

	EFX_POPULATE_OWORD_2(reg, FRF_AB_MD_PRT_ADR, prtad,
			     FRF_AB_MD_DEV_ADR, devad);
	efx_writeo(efx, &reg, FR_AB_MD_ID);

	/* Request data to be read */
	EFX_POPULATE_OWORD_2(reg, FRF_AB_MD_RDC, 1, FRF_AB_MD_GC, 0);
	efx_writeo(efx, &reg, FR_AB_MD_CS);

	/* Wait for data to become available */
	rc = falcon_gmii_wait(efx);
	if (rc == 0) {
		efx_reado(efx, &reg, FR_AB_MD_RXD);
		rc = EFX_OWORD_FIELD(reg, FRF_AB_MD_RXD);
		netif_vdbg(efx, hw, efx->net_dev,
			   "read from MDIO %d register %d.%d, got %04x\n",
			   prtad, devad, addr, rc);
	} else {
		/* Abort the read operation */
		EFX_POPULATE_OWORD_2(reg,
				     FRF_AB_MD_RIC, 0,
				     FRF_AB_MD_GC, 1);
		efx_writeo(efx, &reg, FR_AB_MD_CS);

		netif_dbg(efx, hw, efx->net_dev,
			  "read from MDIO %d register %d.%d, got error %d\n",
			  prtad, devad, addr, rc);
	}

out:
	mutex_unlock(&nic_data->mdio_lock);
	return rc;
}