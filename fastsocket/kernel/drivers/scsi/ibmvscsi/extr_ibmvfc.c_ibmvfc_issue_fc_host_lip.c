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
struct ibmvfc_host {int /*<<< orphan*/  dev; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ibmvfc_reset_host (struct ibmvfc_host*) ; 
 int ibmvfc_wait_while_resetting (struct ibmvfc_host*) ; 
 struct ibmvfc_host* shost_priv (struct Scsi_Host*) ; 

__attribute__((used)) static int ibmvfc_issue_fc_host_lip(struct Scsi_Host *shost)
{
	struct ibmvfc_host *vhost = shost_priv(shost);

	dev_err(vhost->dev, "Initiating host LIP. Resetting connection\n");
	ibmvfc_reset_host(vhost);
	return ibmvfc_wait_while_resetting(vhost);
}