#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int version; int length; int /*<<< orphan*/  opcode; } ;
struct ibmvfc_tmf {int /*<<< orphan*/  cancel_key; int /*<<< orphan*/  scsi_id; TYPE_2__ common; } ;
struct ibmvfc_target {scalar_t__ action; int /*<<< orphan*/  kref; int /*<<< orphan*/  cancel_key; int /*<<< orphan*/  scsi_id; struct ibmvfc_host* vhost; } ;
struct ibmvfc_host {scalar_t__ abort_threads; scalar_t__ state; scalar_t__ action; TYPE_3__* host; } ;
struct TYPE_4__ {struct ibmvfc_tmf tmf; } ;
struct ibmvfc_event {TYPE_1__ iu; struct ibmvfc_target* tgt; } ;
struct TYPE_6__ {int /*<<< orphan*/  host_lock; } ;

/* Variables and functions */
 scalar_t__ IBMVFC_HOST_ACTION_QUERY_TGTS ; 
 scalar_t__ IBMVFC_INITIALIZING ; 
 int /*<<< orphan*/  IBMVFC_MAD_FORMAT ; 
 scalar_t__ IBMVFC_TGT_ACTION_INIT_WAIT ; 
 int /*<<< orphan*/  IBMVFC_TMF_MAD ; 
 int /*<<< orphan*/  __ibmvfc_reset_host (struct ibmvfc_host*) ; 
 int /*<<< orphan*/  default_timeout ; 
 scalar_t__ disc_threads ; 
 struct ibmvfc_event* ibmvfc_get_event (struct ibmvfc_host*) ; 
 int /*<<< orphan*/  ibmvfc_init_event (struct ibmvfc_event*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibmvfc_release_tgt ; 
 int ibmvfc_send_event (struct ibmvfc_event*,struct ibmvfc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibmvfc_tgt_adisc_cancel_done ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ibmvfc_tmf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  tgt_dbg (struct ibmvfc_target*,char*) ; 
 int /*<<< orphan*/  tgt_err (struct ibmvfc_target*,char*,int) ; 

__attribute__((used)) static void ibmvfc_adisc_timeout(struct ibmvfc_target *tgt)
{
	struct ibmvfc_host *vhost = tgt->vhost;
	struct ibmvfc_event *evt;
	struct ibmvfc_tmf *tmf;
	unsigned long flags;
	int rc;

	tgt_dbg(tgt, "ADISC timeout\n");
	spin_lock_irqsave(vhost->host->host_lock, flags);
	if (vhost->abort_threads >= disc_threads ||
	    tgt->action != IBMVFC_TGT_ACTION_INIT_WAIT ||
	    vhost->state != IBMVFC_INITIALIZING ||
	    vhost->action != IBMVFC_HOST_ACTION_QUERY_TGTS) {
		spin_unlock_irqrestore(vhost->host->host_lock, flags);
		return;
	}

	vhost->abort_threads++;
	kref_get(&tgt->kref);
	evt = ibmvfc_get_event(vhost);
	ibmvfc_init_event(evt, ibmvfc_tgt_adisc_cancel_done, IBMVFC_MAD_FORMAT);

	evt->tgt = tgt;
	tmf = &evt->iu.tmf;
	memset(tmf, 0, sizeof(*tmf));
	tmf->common.version = 1;
	tmf->common.opcode = IBMVFC_TMF_MAD;
	tmf->common.length = sizeof(*tmf);
	tmf->scsi_id = tgt->scsi_id;
	tmf->cancel_key = tgt->cancel_key;

	rc = ibmvfc_send_event(evt, vhost, default_timeout);

	if (rc) {
		tgt_err(tgt, "Failed to send cancel event for ADISC. rc=%d\n", rc);
		vhost->abort_threads--;
		kref_put(&tgt->kref, ibmvfc_release_tgt);
		__ibmvfc_reset_host(vhost);
	} else
		tgt_dbg(tgt, "Attempting to cancel ADISC\n");
	spin_unlock_irqrestore(vhost->host->host_lock, flags);
}