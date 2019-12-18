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
struct tcm_loop_tpg {struct tcm_loop_hba* tl_hba; int /*<<< orphan*/  tl_tpg_port_count; } ;
struct tcm_loop_nexus {struct se_session* se_sess; } ;
struct tcm_loop_hba {struct tcm_loop_nexus* tl_nexus; } ;
struct se_session {TYPE_1__* se_node_acl; } ;
struct TYPE_2__ {int /*<<< orphan*/  initiatorname; } ;

/* Variables and functions */
 int ENODEV ; 
 int EPERM ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct tcm_loop_nexus*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__) ; 
 int /*<<< orphan*/  tcm_loop_dump_proto_id (struct tcm_loop_hba*) ; 
 int /*<<< orphan*/  transport_deregister_session (struct se_session*) ; 

__attribute__((used)) static int tcm_loop_drop_nexus(
	struct tcm_loop_tpg *tpg)
{
	struct se_session *se_sess;
	struct tcm_loop_nexus *tl_nexus;
	struct tcm_loop_hba *tl_hba = tpg->tl_hba;

	tl_nexus = tpg->tl_hba->tl_nexus;
	if (!tl_nexus)
		return -ENODEV;

	se_sess = tl_nexus->se_sess;
	if (!se_sess)
		return -ENODEV;

	if (atomic_read(&tpg->tl_tpg_port_count)) {
		pr_err("Unable to remove TCM_Loop I_T Nexus with"
			" active TPG port count: %d\n",
			atomic_read(&tpg->tl_tpg_port_count));
		return -EPERM;
	}

	pr_debug("TCM_Loop_ConfigFS: Removing I_T Nexus to emulated"
		" %s Initiator Port: %s\n", tcm_loop_dump_proto_id(tl_hba),
		tl_nexus->se_sess->se_node_acl->initiatorname);
	/*
	 * Release the SCSI I_T Nexus to the emulated SAS Target Port
	 */
	transport_deregister_session(tl_nexus->se_sess);
	tpg->tl_hba->tl_nexus = NULL;
	kfree(tl_nexus);
	return 0;
}