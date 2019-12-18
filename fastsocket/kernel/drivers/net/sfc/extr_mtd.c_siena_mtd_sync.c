#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mtd_info {struct efx_mtd* priv; } ;
struct efx_nic {int dummy; } ;
struct TYPE_2__ {int updating; int /*<<< orphan*/  nvram_type; } ;
struct efx_mtd_partition {TYPE_1__ mcdi; } ;
struct efx_mtd {struct efx_nic* efx; } ;

/* Variables and functions */
 int efx_mcdi_nvram_update_finish (struct efx_nic*,int /*<<< orphan*/ ) ; 
 struct efx_mtd_partition* to_efx_mtd_partition (struct mtd_info*) ; 

__attribute__((used)) static int siena_mtd_sync(struct mtd_info *mtd)
{
	struct efx_mtd_partition *part = to_efx_mtd_partition(mtd);
	struct efx_mtd *efx_mtd = mtd->priv;
	struct efx_nic *efx = efx_mtd->efx;
	int rc = 0;

	if (part->mcdi.updating) {
		part->mcdi.updating = false;
		rc = efx_mcdi_nvram_update_finish(efx, part->mcdi.nvram_type);
	}

	return rc;
}