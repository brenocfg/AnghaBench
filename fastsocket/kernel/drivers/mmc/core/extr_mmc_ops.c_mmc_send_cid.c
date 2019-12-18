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
typedef  int /*<<< orphan*/  u32 ;
struct mmc_host {TYPE_1__* card; } ;
struct TYPE_2__ {int rca; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MMC_SEND_CID ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_host_is_spi (struct mmc_host*) ; 
 int mmc_send_cxd_data (int /*<<< orphan*/ *,struct mmc_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int mmc_send_cxd_native (struct mmc_host*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int mmc_send_cid(struct mmc_host *host, u32 *cid)
{
	int ret, i;

	if (!mmc_host_is_spi(host)) {
		if (!host->card)
			return -EINVAL;
		return mmc_send_cxd_native(host, host->card->rca << 16,
				cid, MMC_SEND_CID);
	}

	ret = mmc_send_cxd_data(NULL, host, MMC_SEND_CID, cid, 16);
	if (ret)
		return ret;

	for (i = 0;i < 4;i++)
		cid[i] = be32_to_cpu(cid[i]);

	return 0;
}