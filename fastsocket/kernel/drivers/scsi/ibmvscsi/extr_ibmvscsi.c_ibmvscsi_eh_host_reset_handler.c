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
struct scsi_cmnd {TYPE_1__* device; } ;
struct ibmvscsi_host_data {int /*<<< orphan*/  request_limit; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int FAILED ; 
 unsigned long HZ ; 
 int SUCCESS ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ibmvscsi_reset_host (struct ibmvscsi_host_data*) ; 
 unsigned long init_timeout ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct ibmvscsi_host_data* shost_priv (int /*<<< orphan*/ ) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static int ibmvscsi_eh_host_reset_handler(struct scsi_cmnd *cmd)
{
	unsigned long wait_switch = 0;
	struct ibmvscsi_host_data *hostdata = shost_priv(cmd->device->host);

	dev_err(hostdata->dev, "Resetting connection due to error recovery\n");

	ibmvscsi_reset_host(hostdata);

	for (wait_switch = jiffies + (init_timeout * HZ);
	     time_before(jiffies, wait_switch) &&
		     atomic_read(&hostdata->request_limit) < 2;) {

		msleep(10);
	}

	if (atomic_read(&hostdata->request_limit) <= 0)
		return FAILED;

	return SUCCESS;
}