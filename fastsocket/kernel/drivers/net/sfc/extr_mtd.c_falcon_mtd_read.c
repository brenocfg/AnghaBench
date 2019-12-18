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
typedef  int /*<<< orphan*/  u8 ;
struct mtd_info {struct efx_mtd* priv; } ;
struct falcon_nic_data {int /*<<< orphan*/  spi_lock; } ;
struct efx_spi_device {int dummy; } ;
struct efx_nic {struct falcon_nic_data* nic_data; } ;
struct efx_mtd_partition {scalar_t__ offset; } ;
struct efx_mtd {struct efx_nic* efx; struct efx_spi_device* spi; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int falcon_spi_read (struct efx_nic*,struct efx_spi_device const*,scalar_t__,size_t,size_t*,int /*<<< orphan*/ *) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct efx_mtd_partition* to_efx_mtd_partition (struct mtd_info*) ; 

__attribute__((used)) static int falcon_mtd_read(struct mtd_info *mtd, loff_t start,
			   size_t len, size_t *retlen, u8 *buffer)
{
	struct efx_mtd_partition *part = to_efx_mtd_partition(mtd);
	struct efx_mtd *efx_mtd = mtd->priv;
	const struct efx_spi_device *spi = efx_mtd->spi;
	struct efx_nic *efx = efx_mtd->efx;
	struct falcon_nic_data *nic_data = efx->nic_data;
	int rc;

	rc = mutex_lock_interruptible(&nic_data->spi_lock);
	if (rc)
		return rc;
	rc = falcon_spi_read(efx, spi, part->offset + start, len,
			     retlen, buffer);
	mutex_unlock(&nic_data->spi_lock);
	return rc;
}