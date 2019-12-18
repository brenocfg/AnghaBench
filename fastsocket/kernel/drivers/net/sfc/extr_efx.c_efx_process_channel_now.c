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
struct efx_nic {scalar_t__ n_channels; int legacy_irq_enabled; scalar_t__ legacy_irq; int /*<<< orphan*/  loopback_selftest; } ;
struct efx_channel {scalar_t__ channel; int /*<<< orphan*/  napi_str; scalar_t__ eventq_mask; scalar_t__ irq; int /*<<< orphan*/  enabled; struct efx_nic* efx; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  efx_channel_processed (struct efx_channel*) ; 
 int /*<<< orphan*/  efx_nic_disable_interrupts (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_nic_enable_interrupts (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_process_channel (struct efx_channel*,scalar_t__) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_irq (scalar_t__) ; 

void efx_process_channel_now(struct efx_channel *channel)
{
	struct efx_nic *efx = channel->efx;

	BUG_ON(channel->channel >= efx->n_channels);
	BUG_ON(!channel->enabled);
	BUG_ON(!efx->loopback_selftest);

	/* Disable interrupts and wait for ISRs to complete */
	efx_nic_disable_interrupts(efx);
	if (efx->legacy_irq) {
		synchronize_irq(efx->legacy_irq);
		efx->legacy_irq_enabled = false;
	}
	if (channel->irq)
		synchronize_irq(channel->irq);

	/* Wait for any NAPI processing to complete */
	napi_disable(&channel->napi_str);

	/* Poll the channel */
	efx_process_channel(channel, channel->eventq_mask + 1);

	/* Ack the eventq. This may cause an interrupt to be generated
	 * when they are reenabled */
	efx_channel_processed(channel);

	napi_enable(&channel->napi_str);
	if (efx->legacy_irq)
		efx->legacy_irq_enabled = true;
	efx_nic_enable_interrupts(efx);
}