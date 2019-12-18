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
struct se_portal_group {struct tcm_loop_tpg* se_tpg_fabric_ptr; } ;

/* Variables and functions */
#define  SCSI_PROTOCOL_FCP 130 
#define  SCSI_PROTOCOL_ISCSI 129 
#define  SCSI_PROTOCOL_SAS 128 
 char* fc_parse_pr_out_transport_id (struct se_portal_group*,char const*,int /*<<< orphan*/ *,char**) ; 
 char* iscsi_parse_pr_out_transport_id (struct se_portal_group*,char const*,int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 char* sas_parse_pr_out_transport_id (struct se_portal_group*,char const*,int /*<<< orphan*/ *,char**) ; 

__attribute__((used)) static char *tcm_loop_parse_pr_out_transport_id(
	struct se_portal_group *se_tpg,
	const char *buf,
	u32 *out_tid_len,
	char **port_nexus_ptr)
{
	struct tcm_loop_tpg *tl_tpg = se_tpg->se_tpg_fabric_ptr;
	struct tcm_loop_hba *tl_hba = tl_tpg->tl_hba;

	switch (tl_hba->tl_proto_id) {
	case SCSI_PROTOCOL_SAS:
		return sas_parse_pr_out_transport_id(se_tpg, buf, out_tid_len,
					port_nexus_ptr);
	case SCSI_PROTOCOL_FCP:
		return fc_parse_pr_out_transport_id(se_tpg, buf, out_tid_len,
					port_nexus_ptr);
	case SCSI_PROTOCOL_ISCSI:
		return iscsi_parse_pr_out_transport_id(se_tpg, buf, out_tid_len,
					port_nexus_ptr);
	default:
		pr_err("Unknown tl_proto_id: 0x%02x, using"
			" SAS emulation\n", tl_hba->tl_proto_id);
		break;
	}

	return sas_parse_pr_out_transport_id(se_tpg, buf, out_tid_len,
			port_nexus_ptr);
}