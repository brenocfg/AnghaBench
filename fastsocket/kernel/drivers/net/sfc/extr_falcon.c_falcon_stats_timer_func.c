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
struct falcon_nic_data {scalar_t__ stats_disable_count; } ;
struct efx_nic {int /*<<< orphan*/  stats_lock; struct falcon_nic_data* nic_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  falcon_stats_complete (struct efx_nic*) ; 
 int /*<<< orphan*/  falcon_stats_request (struct efx_nic*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void falcon_stats_timer_func(unsigned long context)
{
	struct efx_nic *efx = (struct efx_nic *)context;
	struct falcon_nic_data *nic_data = efx->nic_data;

	spin_lock(&efx->stats_lock);

	falcon_stats_complete(efx);
	if (nic_data->stats_disable_count == 0)
		falcon_stats_request(efx);

	spin_unlock(&efx->stats_lock);
}