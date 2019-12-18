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
typedef  int /*<<< orphan*/  u32 ;
struct tcm_loop_tpg {struct tcm_loop_hba* tl_hba; } ;
struct tcm_loop_hba {int tl_proto_id; } ;
struct t10_pr_registration {int dummy; } ;
struct se_portal_group {struct tcm_loop_tpg* se_tpg_fabric_ptr; } ;
struct se_node_acl {int dummy; } ;

/* Variables and functions */
#define  SCSI_PROTOCOL_FCP 130 
#define  SCSI_PROTOCOL_ISCSI 129 
#define  SCSI_PROTOCOL_SAS 128 
 int /*<<< orphan*/  fc_get_pr_transport_id (struct se_portal_group*,struct se_node_acl*,struct t10_pr_registration*,int*,unsigned char*) ; 
 int /*<<< orphan*/  iscsi_get_pr_transport_id (struct se_portal_group*,struct se_node_acl*,struct t10_pr_registration*,int*,unsigned char*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  sas_get_pr_transport_id (struct se_portal_group*,struct se_node_acl*,struct t10_pr_registration*,int*,unsigned char*) ; 

__attribute__((used)) static u32 tcm_loop_get_pr_transport_id(
	struct se_portal_group *se_tpg,
	struct se_node_acl *se_nacl,
	struct t10_pr_registration *pr_reg,
	int *format_code,
	unsigned char *buf)
{
	struct tcm_loop_tpg *tl_tpg = se_tpg->se_tpg_fabric_ptr;
	struct tcm_loop_hba *tl_hba = tl_tpg->tl_hba;

	switch (tl_hba->tl_proto_id) {
	case SCSI_PROTOCOL_SAS:
		return sas_get_pr_transport_id(se_tpg, se_nacl, pr_reg,
					format_code, buf);
	case SCSI_PROTOCOL_FCP:
		return fc_get_pr_transport_id(se_tpg, se_nacl, pr_reg,
					format_code, buf);
	case SCSI_PROTOCOL_ISCSI:
		return iscsi_get_pr_transport_id(se_tpg, se_nacl, pr_reg,
					format_code, buf);
	default:
		pr_err("Unknown tl_proto_id: 0x%02x, using"
			" SAS emulation\n", tl_hba->tl_proto_id);
		break;
	}

	return sas_get_pr_transport_id(se_tpg, se_nacl, pr_reg,
			format_code, buf);
}