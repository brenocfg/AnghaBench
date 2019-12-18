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
struct ibmvfc_host {int /*<<< orphan*/  host; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int FAILED ; 
 int SUCCESS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fc_block_scsi_eh (struct scsi_cmnd*) ; 
 int ibmvfc_issue_fc_host_lip (int /*<<< orphan*/ ) ; 
 struct ibmvfc_host* shost_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ibmvfc_eh_host_reset_handler(struct scsi_cmnd *cmd)
{
	int rc;
	struct ibmvfc_host *vhost = shost_priv(cmd->device->host);

	fc_block_scsi_eh(cmd);
	dev_err(vhost->dev, "Resetting connection due to error recovery\n");
	rc = ibmvfc_issue_fc_host_lip(vhost->host);
	return rc ? FAILED : SUCCESS;
}