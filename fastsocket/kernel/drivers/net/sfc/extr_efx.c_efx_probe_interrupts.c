#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct msix_entry {unsigned int entry; int /*<<< orphan*/  vector; } ;
struct efx_nic {scalar_t__ interrupt_mode; unsigned int n_channels; unsigned int n_tx_channels; unsigned int n_rx_channels; int rss_spread; TYPE_2__** extra_channel_type; TYPE_3__* pci_dev; int /*<<< orphan*/  legacy_irq; int /*<<< orphan*/  net_dev; TYPE_1__* type; } ;
struct TYPE_9__ {TYPE_2__* type; int /*<<< orphan*/  irq; } ;
struct TYPE_8__ {int /*<<< orphan*/  irq; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* handle_no_channel ) (struct efx_nic*) ;} ;
struct TYPE_6__ {unsigned int phys_addr_channels; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFX_BUG_ON_PARANOID (int) ; 
 scalar_t__ EFX_INT_MODE_LEGACY ; 
 scalar_t__ EFX_INT_MODE_MSI ; 
 scalar_t__ EFX_INT_MODE_MSIX ; 
 int EFX_MAX_CHANNELS ; 
 unsigned int EFX_MAX_EXTRA_CHANNELS ; 
 int /*<<< orphan*/  drv ; 
 TYPE_5__* efx_get_channel (struct efx_nic*,unsigned int) ; 
 int /*<<< orphan*/  efx_sriov_wanted (struct efx_nic*) ; 
 int efx_vf_size (struct efx_nic*) ; 
 unsigned int efx_wanted_parallelism (struct efx_nic*) ; 
 void* max (unsigned int,unsigned int) ; 
 unsigned int min (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  netif_err (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int pci_enable_msi (TYPE_3__*) ; 
 int pci_enable_msix (TYPE_3__*,struct msix_entry*,unsigned int) ; 
 scalar_t__ separate_tx_channels ; 
 int /*<<< orphan*/  stub1 (struct efx_nic*) ; 

__attribute__((used)) static int efx_probe_interrupts(struct efx_nic *efx)
{
	unsigned int max_channels =
		min(efx->type->phys_addr_channels, EFX_MAX_CHANNELS);
	unsigned int extra_channels = 0;
	unsigned int i, j;
	int rc;

	for (i = 0; i < EFX_MAX_EXTRA_CHANNELS; i++)
		if (efx->extra_channel_type[i])
			++extra_channels;

	if (efx->interrupt_mode == EFX_INT_MODE_MSIX) {
		struct msix_entry xentries[EFX_MAX_CHANNELS];
		unsigned int n_channels;

		n_channels = efx_wanted_parallelism(efx);
		if (separate_tx_channels)
			n_channels *= 2;
		n_channels += extra_channels;
		n_channels = min(n_channels, max_channels);

		for (i = 0; i < n_channels; i++)
			xentries[i].entry = i;
		rc = pci_enable_msix(efx->pci_dev, xentries, n_channels);
		if (rc > 0) {
			netif_err(efx, drv, efx->net_dev,
				  "WARNING: Insufficient MSI-X vectors"
				  " available (%d < %u).\n", rc, n_channels);
			netif_err(efx, drv, efx->net_dev,
				  "WARNING: Performance may be reduced.\n");
			EFX_BUG_ON_PARANOID(rc >= n_channels);
			n_channels = rc;
			rc = pci_enable_msix(efx->pci_dev, xentries,
					     n_channels);
		}

		if (rc == 0) {
			efx->n_channels = n_channels;
			if (n_channels > extra_channels)
				n_channels -= extra_channels;
			if (separate_tx_channels) {
				efx->n_tx_channels = max(n_channels / 2, 1U);
				efx->n_rx_channels = max(n_channels -
							 efx->n_tx_channels,
							 1U);
			} else {
				efx->n_tx_channels = n_channels;
				efx->n_rx_channels = n_channels;
			}
			for (i = 0; i < efx->n_channels; i++)
				efx_get_channel(efx, i)->irq =
					xentries[i].vector;
		} else {
			/* Fall back to single channel MSI */
			efx->interrupt_mode = EFX_INT_MODE_MSI;
			netif_err(efx, drv, efx->net_dev,
				  "could not enable MSI-X\n");
		}
	}

	/* Try single interrupt MSI */
	if (efx->interrupt_mode == EFX_INT_MODE_MSI) {
		efx->n_channels = 1;
		efx->n_rx_channels = 1;
		efx->n_tx_channels = 1;
		rc = pci_enable_msi(efx->pci_dev);
		if (rc == 0) {
			efx_get_channel(efx, 0)->irq = efx->pci_dev->irq;
		} else {
			netif_err(efx, drv, efx->net_dev,
				  "could not enable MSI\n");
			efx->interrupt_mode = EFX_INT_MODE_LEGACY;
		}
	}

	/* Assume legacy interrupts */
	if (efx->interrupt_mode == EFX_INT_MODE_LEGACY) {
		efx->n_channels = 1 + (separate_tx_channels ? 1 : 0);
		efx->n_rx_channels = 1;
		efx->n_tx_channels = 1;
		efx->legacy_irq = efx->pci_dev->irq;
	}

	/* Assign extra channels if possible */
	j = efx->n_channels;
	for (i = 0; i < EFX_MAX_EXTRA_CHANNELS; i++) {
		if (!efx->extra_channel_type[i])
			continue;
		if (efx->interrupt_mode != EFX_INT_MODE_MSIX ||
			efx->n_channels <= extra_channels) {
			efx->extra_channel_type[i]->handle_no_channel(efx);
		} else {
			--j;
			efx_get_channel(efx, j)->type =
				efx->extra_channel_type[i];
		}
	}

	/* RSS might be usable on VFs even if it is disabled on the PF */
	efx->rss_spread = ((efx->n_rx_channels > 1 || !efx_sriov_wanted(efx)) ?
			   efx->n_rx_channels : efx_vf_size(efx));

	return 0;
}