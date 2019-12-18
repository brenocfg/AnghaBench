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
struct mtd_info {struct efx_mtd* priv; } ;
struct falcon_nic_data {int /*<<< orphan*/  spi_lock; } ;
struct efx_nic {struct falcon_nic_data* nic_data; } ;
struct efx_mtd_partition {int dummy; } ;
struct efx_mtd {struct efx_nic* efx; } ;

/* Variables and functions */
 int efx_spi_slow_wait (struct efx_mtd_partition*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct efx_mtd_partition* to_efx_mtd_partition (struct mtd_info*) ; 

__attribute__((used)) static int falcon_mtd_sync(struct mtd_info *mtd)
{
	struct efx_mtd_partition *part = to_efx_mtd_partition(mtd);
	struct efx_mtd *efx_mtd = mtd->priv;
	struct efx_nic *efx = efx_mtd->efx;
	struct falcon_nic_data *nic_data = efx->nic_data;
	int rc;

	mutex_lock(&nic_data->spi_lock);
	rc = efx_spi_slow_wait(part, true);
	mutex_unlock(&nic_data->spi_lock);
	return rc;
}