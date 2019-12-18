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
struct efx_nic {scalar_t__ txq_entries; scalar_t__ rxq_entries; int /*<<< orphan*/  net_dev; } ;
struct efx_channel {scalar_t__ eventq_mask; int /*<<< orphan*/  channel; struct efx_nic* efx; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFX_BUG_ON_PARANOID (int) ; 
 unsigned long EFX_MAX_EVQ_SIZE ; 
 int /*<<< orphan*/  EFX_MIN_EVQ_SIZE ; 
 int efx_nic_probe_eventq (struct efx_channel*) ; 
 scalar_t__ max (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_dbg (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  probe ; 
 unsigned long roundup_pow_of_two (scalar_t__) ; 

__attribute__((used)) static int efx_probe_eventq(struct efx_channel *channel)
{
	struct efx_nic *efx = channel->efx;
	unsigned long entries;

	netif_dbg(efx, probe, efx->net_dev,
		  "chan %d create event queue\n", channel->channel);

	/* Build an event queue with room for one event per tx and rx buffer,
	 * plus some extra for link state events and MCDI completions. */
	entries = roundup_pow_of_two(efx->rxq_entries + efx->txq_entries + 128);
	EFX_BUG_ON_PARANOID(entries > EFX_MAX_EVQ_SIZE);
	channel->eventq_mask = max(entries, EFX_MIN_EVQ_SIZE) - 1;

	return efx_nic_probe_eventq(channel);
}