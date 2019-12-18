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
struct mxcmci_host {int /*<<< orphan*/  mmc; int /*<<< orphan*/ * data; int /*<<< orphan*/ * cmd; int /*<<< orphan*/ * req; scalar_t__ base; } ;
struct mmc_request {int dummy; } ;

/* Variables and functions */
 scalar_t__ MMC_REG_INT_CNTR ; 
 int /*<<< orphan*/  mmc_request_done (int /*<<< orphan*/ ,struct mmc_request*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void mxcmci_finish_request(struct mxcmci_host *host,
		struct mmc_request *req)
{
	writel(0, host->base + MMC_REG_INT_CNTR);

	host->req = NULL;
	host->cmd = NULL;
	host->data = NULL;

	mmc_request_done(host->mmc, req);
}