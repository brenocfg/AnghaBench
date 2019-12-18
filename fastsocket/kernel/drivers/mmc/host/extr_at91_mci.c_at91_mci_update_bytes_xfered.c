#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mmc_data {int flags; int bytes_xfered; int blksz; int blocks; } ;
struct at91mci_host {int /*<<< orphan*/  total_length; TYPE_2__* request; } ;
struct TYPE_4__ {struct mmc_data* data; TYPE_1__* cmd; } ;
struct TYPE_3__ {scalar_t__ error; } ;

/* Variables and functions */
 int MMC_DATA_WRITE ; 
 int /*<<< orphan*/  pr_debug (char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void at91_mci_update_bytes_xfered(struct at91mci_host *host)
{
	struct mmc_data *data;

	/* always deal with the effective request (and not the current cmd) */

	if (host->request->cmd && host->request->cmd->error != 0)
		return;

	if (host->request->data) {
		data = host->request->data;
		if (data->flags & MMC_DATA_WRITE) {
			/* card is in IDLE mode now */
			pr_debug("-> bytes_xfered %d, total_length = %d\n",
				data->bytes_xfered, host->total_length);
			data->bytes_xfered = data->blksz * data->blocks;
		}
	}
}