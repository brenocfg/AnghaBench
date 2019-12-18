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
typedef  int /*<<< orphan*/  u32 ;
struct mmc_card {int rca; int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMC_SEND_CSD ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_host_is_spi (int /*<<< orphan*/ ) ; 
 int mmc_send_cxd_data (struct mmc_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int mmc_send_cxd_native (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int mmc_send_csd(struct mmc_card *card, u32 *csd)
{
	int ret, i;

	if (!mmc_host_is_spi(card->host))
		return mmc_send_cxd_native(card->host, card->rca << 16,
				csd, MMC_SEND_CSD);

	ret = mmc_send_cxd_data(card, card->host, MMC_SEND_CSD, csd, 16);
	if (ret)
		return ret;

	for (i = 0;i < 4;i++)
		csd[i] = be32_to_cpu(csd[i]);

	return 0;
}