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
struct ibmvfc_target {int /*<<< orphan*/  kref; int /*<<< orphan*/  scsi_id; struct ibmvfc_host* vhost; } ;
struct TYPE_6__ {int /*<<< orphan*/  service_parms; int /*<<< orphan*/  flags; int /*<<< orphan*/  type; } ;
struct TYPE_5__ {int version; int length; int /*<<< orphan*/  opcode; } ;
struct ibmvfc_process_login {TYPE_3__ parms; int /*<<< orphan*/  scsi_id; TYPE_2__ common; } ;
struct ibmvfc_host {scalar_t__ discovery_threads; } ;
struct TYPE_4__ {struct ibmvfc_process_login prli; } ;
struct ibmvfc_event {TYPE_1__ iu; struct ibmvfc_target* tgt; } ;

/* Variables and functions */
 int /*<<< orphan*/  IBMVFC_MAD_FORMAT ; 
 int /*<<< orphan*/  IBMVFC_PRLI_EST_IMG_PAIR ; 
 int /*<<< orphan*/  IBMVFC_PRLI_INITIATOR_FUNC ; 
 int /*<<< orphan*/  IBMVFC_PROCESS_LOGIN ; 
 int /*<<< orphan*/  IBMVFC_SCSI_FCP_TYPE ; 
 int /*<<< orphan*/  IBMVFC_TGT_ACTION_INIT_WAIT ; 
 int /*<<< orphan*/  IBMVFC_TGT_ACTION_NONE ; 
 int /*<<< orphan*/  default_timeout ; 
 scalar_t__ disc_threads ; 
 struct ibmvfc_event* ibmvfc_get_event (struct ibmvfc_host*) ; 
 int /*<<< orphan*/  ibmvfc_init_event (struct ibmvfc_event*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibmvfc_release_tgt ; 
 scalar_t__ ibmvfc_send_event (struct ibmvfc_event*,struct ibmvfc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibmvfc_set_tgt_action (struct ibmvfc_target*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibmvfc_tgt_prli_done ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ibmvfc_process_login*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tgt_dbg (struct ibmvfc_target*,char*) ; 

__attribute__((used)) static void ibmvfc_tgt_send_prli(struct ibmvfc_target *tgt)
{
	struct ibmvfc_process_login *prli;
	struct ibmvfc_host *vhost = tgt->vhost;
	struct ibmvfc_event *evt;

	if (vhost->discovery_threads >= disc_threads)
		return;

	kref_get(&tgt->kref);
	evt = ibmvfc_get_event(vhost);
	vhost->discovery_threads++;
	ibmvfc_init_event(evt, ibmvfc_tgt_prli_done, IBMVFC_MAD_FORMAT);
	evt->tgt = tgt;
	prli = &evt->iu.prli;
	memset(prli, 0, sizeof(*prli));
	prli->common.version = 1;
	prli->common.opcode = IBMVFC_PROCESS_LOGIN;
	prli->common.length = sizeof(*prli);
	prli->scsi_id = tgt->scsi_id;

	prli->parms.type = IBMVFC_SCSI_FCP_TYPE;
	prli->parms.flags = IBMVFC_PRLI_EST_IMG_PAIR;
	prli->parms.service_parms = IBMVFC_PRLI_INITIATOR_FUNC;

	ibmvfc_set_tgt_action(tgt, IBMVFC_TGT_ACTION_INIT_WAIT);
	if (ibmvfc_send_event(evt, vhost, default_timeout)) {
		vhost->discovery_threads--;
		ibmvfc_set_tgt_action(tgt, IBMVFC_TGT_ACTION_NONE);
		kref_put(&tgt->kref, ibmvfc_release_tgt);
	} else
		tgt_dbg(tgt, "Sent process login\n");
}