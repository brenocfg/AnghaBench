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
struct siena_nic_data {int wol_filter_id; } ;
struct ethtool_wolinfo {int /*<<< orphan*/  sopass; void* wolopts; void* supported; } ;
struct efx_nic {struct siena_nic_data* nic_data; } ;

/* Variables and functions */
 void* WAKE_MAGIC ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void siena_get_wol(struct efx_nic *efx, struct ethtool_wolinfo *wol)
{
	struct siena_nic_data *nic_data = efx->nic_data;

	wol->supported = WAKE_MAGIC;
	if (nic_data->wol_filter_id != -1)
		wol->wolopts = WAKE_MAGIC;
	else
		wol->wolopts = 0;
	memset(&wol->sopass, 0, sizeof(wol->sopass));
}