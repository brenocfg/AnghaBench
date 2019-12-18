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
struct se_portal_group {int /*<<< orphan*/  se_tpg_tfo; } ;
struct tcm_loop_tpg {struct se_portal_group tl_se_tpg; } ;
struct tcm_loop_tmr {int /*<<< orphan*/  tmr_complete; int /*<<< orphan*/  tl_tmr_wait; } ;
struct tcm_loop_nexus {struct se_session* se_sess; } ;
struct tcm_loop_hba {struct tcm_loop_tpg* tl_hba_tpgs; struct tcm_loop_nexus* tl_nexus; } ;
struct se_cmd {TYPE_2__* se_tmr_req; } ;
struct tcm_loop_cmd {int /*<<< orphan*/ * tl_sense_buf; struct se_cmd tl_se_cmd; } ;
struct se_session {int dummy; } ;
struct scsi_cmnd {TYPE_1__* device; } ;
struct TYPE_4__ {scalar_t__ response; } ;
struct TYPE_3__ {size_t id; int /*<<< orphan*/  lun; int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_NONE ; 
 int FAILED ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MSG_SIMPLE_TAG ; 
 int SUCCESS ; 
 scalar_t__ TMR_FUNCTION_COMPLETE ; 
 int /*<<< orphan*/  TMR_LUN_RESET ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int core_tmr_alloc_req (struct se_cmd*,struct tcm_loop_tmr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct tcm_loop_tmr*) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct tcm_loop_cmd*) ; 
 struct tcm_loop_cmd* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tcm_loop_tmr* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ shost_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcm_loop_cmd_cache ; 
 int /*<<< orphan*/  transport_generic_free_cmd (struct se_cmd*,int) ; 
 int /*<<< orphan*/  transport_generic_handle_tmr (struct se_cmd*) ; 
 int /*<<< orphan*/  transport_init_se_cmd (struct se_cmd*,int /*<<< orphan*/ ,struct se_session*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ transport_lookup_tmr_lun (struct se_cmd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tcm_loop_device_reset(struct scsi_cmnd *sc)
{
	struct se_cmd *se_cmd = NULL;
	struct se_portal_group *se_tpg;
	struct se_session *se_sess;
	struct tcm_loop_cmd *tl_cmd = NULL;
	struct tcm_loop_hba *tl_hba;
	struct tcm_loop_nexus *tl_nexus;
	struct tcm_loop_tmr *tl_tmr = NULL;
	struct tcm_loop_tpg *tl_tpg;
	int ret = FAILED, rc;
	/*
	 * Locate the tcm_loop_hba_t pointer
	 */
	tl_hba = *(struct tcm_loop_hba **)shost_priv(sc->device->host);
	/*
	 * Locate the tl_nexus and se_sess pointers
	 */
	tl_nexus = tl_hba->tl_nexus;
	if (!tl_nexus) {
		pr_err("Unable to perform device reset without"
				" active I_T Nexus\n");
		return FAILED;
	}
	se_sess = tl_nexus->se_sess;
	/*
	 * Locate the tl_tpg and se_tpg pointers from TargetID in sc->device->id
	 */
	tl_tpg = &tl_hba->tl_hba_tpgs[sc->device->id];
	se_tpg = &tl_tpg->tl_se_tpg;

	tl_cmd = kmem_cache_zalloc(tcm_loop_cmd_cache, GFP_KERNEL);
	if (!tl_cmd) {
		pr_err("Unable to allocate memory for tl_cmd\n");
		return FAILED;
	}

	tl_tmr = kzalloc(sizeof(struct tcm_loop_tmr), GFP_KERNEL);
	if (!tl_tmr) {
		pr_err("Unable to allocate memory for tl_tmr\n");
		goto release;
	}
	init_waitqueue_head(&tl_tmr->tl_tmr_wait);

	se_cmd = &tl_cmd->tl_se_cmd;
	/*
	 * Initialize struct se_cmd descriptor from target_core_mod infrastructure
	 */
	transport_init_se_cmd(se_cmd, se_tpg->se_tpg_tfo, se_sess, 0,
				DMA_NONE, MSG_SIMPLE_TAG,
				&tl_cmd->tl_sense_buf[0]);

	rc = core_tmr_alloc_req(se_cmd, tl_tmr, TMR_LUN_RESET, GFP_KERNEL);
	if (rc < 0)
		goto release;
	/*
	 * Locate the underlying TCM struct se_lun from sc->device->lun
	 */
	if (transport_lookup_tmr_lun(se_cmd, sc->device->lun) < 0)
		goto release;
	/*
	 * Queue the TMR to TCM Core and sleep waiting for tcm_loop_queue_tm_rsp()
	 * to wake us up.
	 */
	transport_generic_handle_tmr(se_cmd);
	wait_event(tl_tmr->tl_tmr_wait, atomic_read(&tl_tmr->tmr_complete));
	/*
	 * The TMR LUN_RESET has completed, check the response status and
	 * then release allocations.
	 */
	ret = (se_cmd->se_tmr_req->response == TMR_FUNCTION_COMPLETE) ?
		SUCCESS : FAILED;
release:
	if (se_cmd)
		transport_generic_free_cmd(se_cmd, 1);
	else
		kmem_cache_free(tcm_loop_cmd_cache, tl_cmd);
	kfree(tl_tmr);
	return ret;
}