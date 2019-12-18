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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct mmc_card {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  mmc_claim_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_release_host (int /*<<< orphan*/ ) ; 
 int mmc_send_status (void*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mmc_dbg_card_status_get(void *data, u64 *val)
{
	struct mmc_card	*card = data;
	u32		status;
	int		ret;

	mmc_claim_host(card->host);

	ret = mmc_send_status(data, &status);
	if (!ret)
		*val = status;

	mmc_release_host(card->host);

	return ret;
}