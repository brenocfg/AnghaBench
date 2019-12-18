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
struct efx_mtd_partition {scalar_t__ offset; } ;
struct efx_mtd {struct efx_nic* efx; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int efx_spi_erase (struct efx_mtd_partition*,scalar_t__,size_t) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct efx_mtd_partition* to_efx_mtd_partition (struct mtd_info*) ; 

__attribute__((used)) static int falcon_mtd_erase(struct mtd_info *mtd, loff_t start, size_t len)
{
	struct efx_mtd_partition *part = to_efx_mtd_partition(mtd);
	struct efx_mtd *efx_mtd = mtd->priv;
	struct efx_nic *efx = efx_mtd->efx;
	struct falcon_nic_data *nic_data = efx->nic_data;
	int rc;

	rc = mutex_lock_interruptible(&nic_data->spi_lock);
	if (rc)
		return rc;
	rc = efx_spi_erase(part, part->offset + start, len);
	mutex_unlock(&nic_data->spi_lock);
	return rc;
}