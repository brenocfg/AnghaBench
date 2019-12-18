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
struct siena_nic_data {int dummy; } ;
struct TYPE_5__ {int dma_addr; int /*<<< orphan*/  addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  prtad; } ;
struct efx_nic {struct siena_nic_data* nic_data; TYPE_2__ irq_status; TYPE_1__ mdio; int /*<<< orphan*/  phy_type; int /*<<< orphan*/  net_dev; scalar_t__ port_num; } ;
typedef  int /*<<< orphan*/  efx_oword_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ EFX_OWORD_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FRF_CZ_CS_PORT_NUM ; 
 int /*<<< orphan*/  FR_AZ_CS_DEBUG ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MDIO_PRTAD_NONE ; 
 int /*<<< orphan*/  PHY_TYPE_NONE ; 
 int /*<<< orphan*/  RESET_TYPE_ALL ; 
 int efx_mcdi_drv_attach (struct efx_nic*,int,int*) ; 
 int efx_mcdi_handle_assertion (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_mcdi_init (struct efx_nic*) ; 
 int efx_mcdi_mon_probe (struct efx_nic*) ; 
 int efx_nic_alloc_buffer (struct efx_nic*,TYPE_2__*,int) ; 
 scalar_t__ efx_nic_fpga_ver (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_nic_free_buffer (struct efx_nic*,TYPE_2__*) ; 
 int /*<<< orphan*/  efx_ptp_probe (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_reado (struct efx_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_sriov_probe (struct efx_nic*) ; 
 int /*<<< orphan*/  kfree (struct siena_nic_data*) ; 
 struct siena_nic_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_dbg (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,unsigned long long,int /*<<< orphan*/ ,unsigned long long) ; 
 int /*<<< orphan*/  netif_err (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  probe ; 
 int /*<<< orphan*/  siena_init_wol (struct efx_nic*) ; 
 int siena_probe_nvconfig (struct efx_nic*) ; 
 int siena_reset_hw (struct efx_nic*,int /*<<< orphan*/ ) ; 
 scalar_t__ virt_to_phys (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int siena_probe_nic(struct efx_nic *efx)
{
	struct siena_nic_data *nic_data;
	bool already_attached = false;
	efx_oword_t reg;
	int rc;

	/* Allocate storage for hardware specific data */
	nic_data = kzalloc(sizeof(struct siena_nic_data), GFP_KERNEL);
	if (!nic_data)
		return -ENOMEM;
	efx->nic_data = nic_data;

	if (efx_nic_fpga_ver(efx) != 0) {
		netif_err(efx, probe, efx->net_dev,
			  "Siena FPGA not supported\n");
		rc = -ENODEV;
		goto fail1;
	}

	efx_reado(efx, &reg, FR_AZ_CS_DEBUG);
	efx->port_num = EFX_OWORD_FIELD(reg, FRF_CZ_CS_PORT_NUM) - 1;

	efx_mcdi_init(efx);

	/* Recover from a failed assertion before probing */
	rc = efx_mcdi_handle_assertion(efx);
	if (rc)
		goto fail1;

	/* Let the BMC know that the driver is now in charge of link and
	 * filter settings. We must do this before we reset the NIC */
	rc = efx_mcdi_drv_attach(efx, true, &already_attached);
	if (rc) {
		netif_err(efx, probe, efx->net_dev,
			  "Unable to register driver with MCPU\n");
		goto fail2;
	}
	if (already_attached)
		/* Not a fatal error */
		netif_err(efx, probe, efx->net_dev,
			  "Host already registered with MCPU\n");

	/* Now we can reset the NIC */
	rc = siena_reset_hw(efx, RESET_TYPE_ALL);
	if (rc) {
		netif_err(efx, probe, efx->net_dev, "failed to reset NIC\n");
		goto fail3;
	}

	siena_init_wol(efx);

	/* Allocate memory for INT_KER */
	rc = efx_nic_alloc_buffer(efx, &efx->irq_status, sizeof(efx_oword_t));
	if (rc)
		goto fail4;
	BUG_ON(efx->irq_status.dma_addr & 0x0f);

	netif_dbg(efx, probe, efx->net_dev,
		  "INT_KER at %llx (virt %p phys %llx)\n",
		  (unsigned long long)efx->irq_status.dma_addr,
		  efx->irq_status.addr,
		  (unsigned long long)virt_to_phys(efx->irq_status.addr));

	/* Read in the non-volatile configuration */
	rc = siena_probe_nvconfig(efx);
	if (rc == -EINVAL) {
		netif_err(efx, probe, efx->net_dev,
			  "NVRAM is invalid therefore using defaults\n");
		efx->phy_type = PHY_TYPE_NONE;
		efx->mdio.prtad = MDIO_PRTAD_NONE;
	} else if (rc) {
		goto fail5;
	}

	rc = efx_mcdi_mon_probe(efx);
	if (rc)
		goto fail5;

	efx_sriov_probe(efx);
	efx_ptp_probe(efx);

	return 0;

fail5:
	efx_nic_free_buffer(efx, &efx->irq_status);
fail4:
fail3:
	efx_mcdi_drv_attach(efx, false, NULL);
fail2:
fail1:
	kfree(efx->nic_data);
	return rc;
}