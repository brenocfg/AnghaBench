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
typedef  int u32 ;
struct ibmvfc_target {scalar_t__ scsi_id; scalar_t__ new_scsi_id; int /*<<< orphan*/  kref; } ;
struct TYPE_4__ {int status; } ;
struct ibmvfc_implicit_logout {TYPE_2__ common; } ;
struct ibmvfc_host {scalar_t__ action; int /*<<< orphan*/  work_wait_q; int /*<<< orphan*/  discovery_threads; } ;
struct ibmvfc_event {TYPE_1__* xfer_iu; struct ibmvfc_host* vhost; struct ibmvfc_target* tgt; } ;
struct TYPE_3__ {struct ibmvfc_implicit_logout implicit_logout; } ;

/* Variables and functions */
 scalar_t__ IBMVFC_HOST_ACTION_QUERY_TGTS ; 
 scalar_t__ IBMVFC_HOST_ACTION_TGT_INIT ; 
#define  IBMVFC_MAD_DRIVER_FAILED 130 
#define  IBMVFC_MAD_FAILED 129 
#define  IBMVFC_MAD_SUCCESS 128 
 int /*<<< orphan*/  IBMVFC_TGT_ACTION_DEL_RPORT ; 
 int /*<<< orphan*/  IBMVFC_TGT_ACTION_NONE ; 
 int /*<<< orphan*/  ibmvfc_free_event (struct ibmvfc_event*) ; 
 int /*<<< orphan*/  ibmvfc_init_tgt (struct ibmvfc_target*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibmvfc_release_tgt ; 
 int /*<<< orphan*/  ibmvfc_set_tgt_action (struct ibmvfc_target*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibmvfc_tgt_send_plogi ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tgt_dbg (struct ibmvfc_target*,char*) ; 
 int /*<<< orphan*/  tgt_err (struct ibmvfc_target*,char*,int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ibmvfc_tgt_implicit_logout_done(struct ibmvfc_event *evt)
{
	struct ibmvfc_target *tgt = evt->tgt;
	struct ibmvfc_host *vhost = evt->vhost;
	struct ibmvfc_implicit_logout *rsp = &evt->xfer_iu->implicit_logout;
	u32 status = rsp->common.status;

	vhost->discovery_threads--;
	ibmvfc_free_event(evt);
	ibmvfc_set_tgt_action(tgt, IBMVFC_TGT_ACTION_NONE);

	switch (status) {
	case IBMVFC_MAD_SUCCESS:
		tgt_dbg(tgt, "Implicit Logout succeeded\n");
		break;
	case IBMVFC_MAD_DRIVER_FAILED:
		kref_put(&tgt->kref, ibmvfc_release_tgt);
		wake_up(&vhost->work_wait_q);
		return;
	case IBMVFC_MAD_FAILED:
	default:
		tgt_err(tgt, "Implicit Logout failed: rc=0x%02X\n", status);
		break;
	};

	if (vhost->action == IBMVFC_HOST_ACTION_TGT_INIT)
		ibmvfc_init_tgt(tgt, ibmvfc_tgt_send_plogi);
	else if (vhost->action == IBMVFC_HOST_ACTION_QUERY_TGTS &&
		 tgt->scsi_id != tgt->new_scsi_id)
		ibmvfc_set_tgt_action(tgt, IBMVFC_TGT_ACTION_DEL_RPORT);
	kref_put(&tgt->kref, ibmvfc_release_tgt);
	wake_up(&vhost->work_wait_q);
}