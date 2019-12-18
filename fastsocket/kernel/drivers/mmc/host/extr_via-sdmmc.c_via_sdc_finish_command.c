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
struct via_crdr_mmc_host {TYPE_1__* cmd; int /*<<< orphan*/  finish_tasklet; } ;
struct TYPE_2__ {int /*<<< orphan*/  data; scalar_t__ error; } ;

/* Variables and functions */
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  via_sdc_get_response (struct via_crdr_mmc_host*,TYPE_1__*) ; 

__attribute__((used)) static void via_sdc_finish_command(struct via_crdr_mmc_host *host)
{
	via_sdc_get_response(host, host->cmd);

	host->cmd->error = 0;

	if (!host->cmd->data)
		tasklet_schedule(&host->finish_tasklet);

	host->cmd = NULL;
}