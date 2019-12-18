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
struct efx_ptp_data {int reset_required; int rxfilter_event; int rxfilter_general; int rxfilter_installed; scalar_t__ current_adjfreq; scalar_t__ evt_frag_idx; int /*<<< orphan*/  channel; } ;
struct efx_nic {struct efx_ptp_data* ptp_data; } ;
struct efx_filter_spec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFX_FILTER_PRI_REQUIRED ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int /*<<< orphan*/  PTP_ADDRESS ; 
 int /*<<< orphan*/  PTP_EVENT_PORT ; 
 int /*<<< orphan*/  PTP_GENERAL_PORT ; 
 int /*<<< orphan*/  efx_channel_get_rx_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_filter_init_rx (struct efx_filter_spec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int efx_filter_insert_filter (struct efx_nic*,struct efx_filter_spec*,int) ; 
 int /*<<< orphan*/  efx_filter_remove_id_safe (struct efx_nic*,int /*<<< orphan*/ ,int) ; 
 int efx_filter_set_ipv4_local (struct efx_filter_spec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int efx_ptp_enable (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_rx_queue_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int efx_ptp_start(struct efx_nic *efx)
{
	struct efx_ptp_data *ptp = efx->ptp_data;
	struct efx_filter_spec rxfilter;
	int rc;

	ptp->reset_required = false;

	/* Must filter on both event and general ports to ensure
	 * that there is no packet re-ordering.
	 */
	efx_filter_init_rx(&rxfilter, EFX_FILTER_PRI_REQUIRED, 0,
			   efx_rx_queue_index(
				   efx_channel_get_rx_queue(ptp->channel)));
	rc = efx_filter_set_ipv4_local(&rxfilter, IPPROTO_UDP,
				       htonl(PTP_ADDRESS),
				       htons(PTP_EVENT_PORT));
	if (rc != 0)
		return rc;

	rc = efx_filter_insert_filter(efx, &rxfilter, true);
	if (rc < 0)
		return rc;
	ptp->rxfilter_event = rc;

	efx_filter_init_rx(&rxfilter, EFX_FILTER_PRI_REQUIRED, 0,
			   efx_rx_queue_index(
				   efx_channel_get_rx_queue(ptp->channel)));
	rc = efx_filter_set_ipv4_local(&rxfilter, IPPROTO_UDP,
				       htonl(PTP_ADDRESS),
				       htons(PTP_GENERAL_PORT));
	if (rc != 0)
		goto fail;

	rc = efx_filter_insert_filter(efx, &rxfilter, true);
	if (rc < 0)
		goto fail;
	ptp->rxfilter_general = rc;

	rc = efx_ptp_enable(efx);
	if (rc != 0)
		goto fail2;

	ptp->evt_frag_idx = 0;
	ptp->current_adjfreq = 0;
	ptp->rxfilter_installed = true;

	return 0;

fail2:
	efx_filter_remove_id_safe(efx, EFX_FILTER_PRI_REQUIRED,
				  ptp->rxfilter_general);
fail:
	efx_filter_remove_id_safe(efx, EFX_FILTER_PRI_REQUIRED,
				  ptp->rxfilter_event);

	return rc;
}