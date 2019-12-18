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
struct mmc_request {scalar_t__ stop; } ;
struct mmc_data {int dummy; } ;
struct imxmci_host {int /*<<< orphan*/  mmc; struct mmc_request* req; struct mmc_data* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int imxmci_finish_data (struct imxmci_host*,unsigned int) ; 
 int /*<<< orphan*/  imxmci_finish_request (struct imxmci_host*,struct mmc_request*) ; 
 int /*<<< orphan*/  imxmci_start_cmd (struct imxmci_host*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imxmci_stop_clock (struct imxmci_host*) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int imxmci_data_done(struct imxmci_host *host, unsigned int stat)
{
	struct mmc_data *data = host->data;
	int data_error;

	if (!data)
		return 0;

	data_error = imxmci_finish_data(host, stat);

	if (host->req->stop) {
		imxmci_stop_clock(host);
		imxmci_start_cmd(host, host->req->stop, 0);
	} else {
		struct mmc_request *req;
		req = host->req;
		if (req)
			imxmci_finish_request(host, req);
		else
			dev_warn(mmc_dev(host->mmc), "imxmci_data_done: no request to finish\n");
	}

	return 1;
}