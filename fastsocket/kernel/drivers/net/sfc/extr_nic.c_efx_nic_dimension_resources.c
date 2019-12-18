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
struct efx_nic {int n_rx_channels; int n_tx_channels; int n_channels; unsigned int vf_buftbl_base; unsigned int vi_scale; unsigned int vf_count; unsigned int tx_dc_base; unsigned int rx_dc_base; int /*<<< orphan*/  net_dev; } ;
typedef  int /*<<< orphan*/  efx_qword_t ;

/* Variables and functions */
 int EFX_BUF_SIZE ; 
 int EFX_MAX_DMAQ_SIZE ; 
 int EFX_MAX_EVQ_SIZE ; 
 int EFX_TXQ_TYPES ; 
 unsigned int EFX_VF_BUFTBL_PER_VI ; 
 unsigned int EFX_VI_BASE ; 
 unsigned int RX_DC_ENTRIES ; 
 unsigned int TX_DC_ENTRIES ; 
 scalar_t__ efx_sriov_wanted (struct efx_nic*) ; 
 unsigned int efx_vf_size (struct efx_nic*) ; 
 unsigned int max (unsigned int,unsigned int) ; 
 unsigned int min (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  netif_err (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  probe ; 

void efx_nic_dimension_resources(struct efx_nic *efx, unsigned sram_lim_qw)
{
	unsigned vi_count, buftbl_min;

	/* Account for the buffer table entries backing the datapath channels
	 * and the descriptor caches for those channels.
	 */
	buftbl_min = ((efx->n_rx_channels * EFX_MAX_DMAQ_SIZE +
		       efx->n_tx_channels * EFX_TXQ_TYPES * EFX_MAX_DMAQ_SIZE +
		       efx->n_channels * EFX_MAX_EVQ_SIZE)
		      * sizeof(efx_qword_t) / EFX_BUF_SIZE);
	vi_count = max(efx->n_channels, efx->n_tx_channels * EFX_TXQ_TYPES);

#ifdef CONFIG_SFC_SRIOV
	if (efx_sriov_wanted(efx)) {
		unsigned vi_dc_entries, buftbl_free, entries_per_vf, vf_limit;

		efx->vf_buftbl_base = buftbl_min;

		vi_dc_entries = RX_DC_ENTRIES + TX_DC_ENTRIES;
		vi_count = max(vi_count, EFX_VI_BASE);
		buftbl_free = (sram_lim_qw - buftbl_min -
			       vi_count * vi_dc_entries);

		entries_per_vf = ((vi_dc_entries + EFX_VF_BUFTBL_PER_VI) *
				  efx_vf_size(efx));
		vf_limit = min(buftbl_free / entries_per_vf,
			       (1024U - EFX_VI_BASE) >> efx->vi_scale);

		if (efx->vf_count > vf_limit) {
			netif_err(efx, probe, efx->net_dev,
				  "Reducing VF count from from %d to %d\n",
				  efx->vf_count, vf_limit);
			efx->vf_count = vf_limit;
		}
		vi_count += efx->vf_count * efx_vf_size(efx);
	}
#endif

	efx->tx_dc_base = sram_lim_qw - vi_count * TX_DC_ENTRIES;
	efx->rx_dc_base = efx->tx_dc_base - vi_count * RX_DC_ENTRIES;
}