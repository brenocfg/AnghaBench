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
struct t10_pr_registration {scalar_t__ pr_reg_all_tg_pt; int /*<<< orphan*/  pr_res_type; } ;
struct se_portal_group {TYPE_1__* se_tpg_tfo; } ;
struct se_node_acl {int /*<<< orphan*/  initiatorname; } ;
struct se_device {int /*<<< orphan*/  dev_reservation_lock; struct t10_pr_registration* dev_pr_res_holder; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_fabric_name ) () ;} ;

/* Variables and functions */
 int PR_REG_ISID_ID_LEN ; 
 int core_pr_dump_initiator_port (struct t10_pr_registration*,char*,int) ; 
 int /*<<< orphan*/  core_scsi3_pr_dump_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 () ; 

__attribute__((used)) static void core_scsi3_aptpl_reserve(
	struct se_device *dev,
	struct se_portal_group *tpg,
	struct se_node_acl *node_acl,
	struct t10_pr_registration *pr_reg)
{
	char i_buf[PR_REG_ISID_ID_LEN];
	int prf_isid;

	memset(i_buf, 0, PR_REG_ISID_ID_LEN);
	prf_isid = core_pr_dump_initiator_port(pr_reg, &i_buf[0],
				PR_REG_ISID_ID_LEN);

	spin_lock(&dev->dev_reservation_lock);
	dev->dev_pr_res_holder = pr_reg;
	spin_unlock(&dev->dev_reservation_lock);

	pr_debug("SPC-3 PR [%s] Service Action: APTPL RESERVE created"
		" new reservation holder TYPE: %s ALL_TG_PT: %d\n",
		tpg->se_tpg_tfo->get_fabric_name(),
		core_scsi3_pr_dump_type(pr_reg->pr_res_type),
		(pr_reg->pr_reg_all_tg_pt) ? 1 : 0);
	pr_debug("SPC-3 PR [%s] RESERVE Node: %s%s\n",
		tpg->se_tpg_tfo->get_fabric_name(), node_acl->initiatorname,
		(prf_isid) ? &i_buf[0] : "");
}