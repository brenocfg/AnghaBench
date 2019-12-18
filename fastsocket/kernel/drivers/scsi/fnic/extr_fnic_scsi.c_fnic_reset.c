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
struct fnic {TYPE_2__* lport; } ;
struct TYPE_3__ {scalar_t__ (* lport_reset ) (struct fc_lport*) ;} ;
struct fc_lport {TYPE_1__ tt; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int FAILED ; 
 int /*<<< orphan*/  FNIC_SCSI_DBG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int SUCCESS ; 
 struct fnic* lport_priv (struct fc_lport*) ; 
 struct fc_lport* shost_priv (struct Scsi_Host*) ; 
 scalar_t__ stub1 (struct fc_lport*) ; 

int fnic_reset(struct Scsi_Host *shost)
{
	struct fc_lport *lp;
	struct fnic *fnic;
	int ret = SUCCESS;

	lp = shost_priv(shost);
	fnic = lport_priv(lp);

	FNIC_SCSI_DBG(KERN_DEBUG, fnic->lport->host,
		      "fnic_reset called\n");

	/*
	 * Reset local port, this will clean up libFC exchanges,
	 * reset remote port sessions, and if link is up, begin flogi
	 */
	if (lp->tt.lport_reset(lp))
		ret = FAILED;

	FNIC_SCSI_DBG(KERN_DEBUG, fnic->lport->host,
		      "Returning from fnic reset %s\n",
		      (ret == SUCCESS) ?
		      "SUCCESS" : "FAILED");

	return ret;
}