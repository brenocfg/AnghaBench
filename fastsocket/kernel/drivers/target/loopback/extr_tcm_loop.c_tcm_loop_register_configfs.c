#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * fabric_drop_np; int /*<<< orphan*/ * fabric_make_np; int /*<<< orphan*/ * fabric_pre_unlink; int /*<<< orphan*/ * fabric_post_link; int /*<<< orphan*/ * fabric_drop_tpg; int /*<<< orphan*/ * fabric_make_tpg; int /*<<< orphan*/ * fabric_drop_wwn; int /*<<< orphan*/ * fabric_make_wwn; int /*<<< orphan*/ * queue_tm_rsp; int /*<<< orphan*/ * queue_status; int /*<<< orphan*/ * queue_data_in; int /*<<< orphan*/ * get_cmd_state; int /*<<< orphan*/ * get_task_tag; int /*<<< orphan*/ * set_default_node_attributes; int /*<<< orphan*/ * write_pending_status; int /*<<< orphan*/ * write_pending; int /*<<< orphan*/ * sess_get_initiator_sid; int /*<<< orphan*/ * sess_get_index; int /*<<< orphan*/ * close_session; int /*<<< orphan*/ * shutdown_session; int /*<<< orphan*/ * release_cmd; int /*<<< orphan*/ * check_stop_free; int /*<<< orphan*/ * tpg_get_inst_index; int /*<<< orphan*/ * tpg_release_fabric_acl; int /*<<< orphan*/ * tpg_alloc_fabric_acl; int /*<<< orphan*/ * tpg_check_prod_mode_write_protect; int /*<<< orphan*/ * tpg_check_demo_mode_write_protect; int /*<<< orphan*/ * tpg_check_demo_mode_cache; int /*<<< orphan*/ * tpg_check_demo_mode; int /*<<< orphan*/ * tpg_parse_pr_out_transport_id; int /*<<< orphan*/ * tpg_get_pr_transport_id_len; int /*<<< orphan*/ * tpg_get_pr_transport_id; int /*<<< orphan*/ * tpg_get_default_depth; int /*<<< orphan*/ * tpg_get_tag; int /*<<< orphan*/ * tpg_get_wwn; int /*<<< orphan*/ * get_fabric_proto_ident; int /*<<< orphan*/ * get_fabric_name; } ;
struct target_fabric_configfs {TYPE_1__ tf_ops; } ;
struct TYPE_13__ {int /*<<< orphan*/ * ct_attrs; } ;
struct TYPE_12__ {int /*<<< orphan*/ * ct_attrs; } ;
struct TYPE_11__ {int /*<<< orphan*/ * ct_attrs; } ;
struct TYPE_10__ {int /*<<< orphan*/  ct_attrs; } ;
struct TYPE_9__ {int /*<<< orphan*/  ct_attrs; } ;
struct TYPE_14__ {TYPE_6__ tfc_tpg_np_base_cit; TYPE_5__ tfc_tpg_param_cit; TYPE_4__ tfc_tpg_attrib_cit; TYPE_3__ tfc_tpg_base_cit; TYPE_2__ tfc_wwn_cit; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct target_fabric_configfs*) ; 
 int PTR_ERR (struct target_fabric_configfs*) ; 
 TYPE_7__* TF_CIT_TMPL (struct target_fabric_configfs*) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  target_fabric_configfs_free (struct target_fabric_configfs*) ; 
 struct target_fabric_configfs* target_fabric_configfs_init (int /*<<< orphan*/ ,char*) ; 
 int target_fabric_configfs_register (struct target_fabric_configfs*) ; 
 int /*<<< orphan*/  tcm_loop_check_demo_mode ; 
 int /*<<< orphan*/  tcm_loop_check_demo_mode_cache ; 
 int /*<<< orphan*/  tcm_loop_check_demo_mode_write_protect ; 
 int /*<<< orphan*/  tcm_loop_check_prod_mode_write_protect ; 
 int /*<<< orphan*/  tcm_loop_check_stop_free ; 
 int /*<<< orphan*/  tcm_loop_close_session ; 
 int /*<<< orphan*/  tcm_loop_drop_naa_tpg ; 
 int /*<<< orphan*/  tcm_loop_drop_scsi_hba ; 
 struct target_fabric_configfs* tcm_loop_fabric_configfs ; 
 int /*<<< orphan*/  tcm_loop_get_cmd_state ; 
 int /*<<< orphan*/  tcm_loop_get_default_depth ; 
 int /*<<< orphan*/  tcm_loop_get_endpoint_wwn ; 
 int /*<<< orphan*/  tcm_loop_get_fabric_name ; 
 int /*<<< orphan*/  tcm_loop_get_fabric_proto_ident ; 
 int /*<<< orphan*/  tcm_loop_get_inst_index ; 
 int /*<<< orphan*/  tcm_loop_get_pr_transport_id ; 
 int /*<<< orphan*/  tcm_loop_get_pr_transport_id_len ; 
 int /*<<< orphan*/  tcm_loop_get_tag ; 
 int /*<<< orphan*/  tcm_loop_get_task_tag ; 
 scalar_t__ tcm_loop_hba_no_cnt ; 
 int /*<<< orphan*/  tcm_loop_make_naa_tpg ; 
 int /*<<< orphan*/  tcm_loop_make_scsi_hba ; 
 int /*<<< orphan*/  tcm_loop_parse_pr_out_transport_id ; 
 int /*<<< orphan*/  tcm_loop_port_link ; 
 int /*<<< orphan*/  tcm_loop_port_unlink ; 
 int /*<<< orphan*/  tcm_loop_queue_data_in ; 
 int /*<<< orphan*/  tcm_loop_queue_status ; 
 int /*<<< orphan*/  tcm_loop_queue_tm_rsp ; 
 int /*<<< orphan*/  tcm_loop_release_cmd ; 
 int /*<<< orphan*/  tcm_loop_sess_get_index ; 
 int /*<<< orphan*/  tcm_loop_set_default_node_attributes ; 
 int /*<<< orphan*/  tcm_loop_shutdown_session ; 
 int /*<<< orphan*/  tcm_loop_tpg_alloc_fabric_acl ; 
 int /*<<< orphan*/  tcm_loop_tpg_attrs ; 
 int /*<<< orphan*/  tcm_loop_tpg_release_fabric_acl ; 
 int /*<<< orphan*/  tcm_loop_write_pending ; 
 int /*<<< orphan*/  tcm_loop_write_pending_status ; 
 int /*<<< orphan*/  tcm_loop_wwn_attrs ; 

__attribute__((used)) static int tcm_loop_register_configfs(void)
{
	struct target_fabric_configfs *fabric;
	int ret;
	/*
	 * Set the TCM Loop HBA counter to zero
	 */
	tcm_loop_hba_no_cnt = 0;
	/*
	 * Register the top level struct config_item_type with TCM core
	 */
	fabric = target_fabric_configfs_init(THIS_MODULE, "loopback");
	if (IS_ERR(fabric)) {
		pr_err("tcm_loop_register_configfs() failed!\n");
		return PTR_ERR(fabric);
	}
	/*
	 * Setup the fabric API of function pointers used by target_core_mod
	 */
	fabric->tf_ops.get_fabric_name = &tcm_loop_get_fabric_name;
	fabric->tf_ops.get_fabric_proto_ident = &tcm_loop_get_fabric_proto_ident;
	fabric->tf_ops.tpg_get_wwn = &tcm_loop_get_endpoint_wwn;
	fabric->tf_ops.tpg_get_tag = &tcm_loop_get_tag;
	fabric->tf_ops.tpg_get_default_depth = &tcm_loop_get_default_depth;
	fabric->tf_ops.tpg_get_pr_transport_id = &tcm_loop_get_pr_transport_id;
	fabric->tf_ops.tpg_get_pr_transport_id_len =
					&tcm_loop_get_pr_transport_id_len;
	fabric->tf_ops.tpg_parse_pr_out_transport_id =
					&tcm_loop_parse_pr_out_transport_id;
	fabric->tf_ops.tpg_check_demo_mode = &tcm_loop_check_demo_mode;
	fabric->tf_ops.tpg_check_demo_mode_cache =
					&tcm_loop_check_demo_mode_cache;
	fabric->tf_ops.tpg_check_demo_mode_write_protect =
					&tcm_loop_check_demo_mode_write_protect;
	fabric->tf_ops.tpg_check_prod_mode_write_protect =
					&tcm_loop_check_prod_mode_write_protect;
	/*
	 * The TCM loopback fabric module runs in demo-mode to a local
	 * virtual SCSI device, so fabric dependent initator ACLs are
	 * not required.
	 */
	fabric->tf_ops.tpg_alloc_fabric_acl = &tcm_loop_tpg_alloc_fabric_acl;
	fabric->tf_ops.tpg_release_fabric_acl =
					&tcm_loop_tpg_release_fabric_acl;
	fabric->tf_ops.tpg_get_inst_index = &tcm_loop_get_inst_index;
	/*
	 * Used for setting up remaining TCM resources in process context
	 */
	fabric->tf_ops.check_stop_free = &tcm_loop_check_stop_free;
	fabric->tf_ops.release_cmd = &tcm_loop_release_cmd;
	fabric->tf_ops.shutdown_session = &tcm_loop_shutdown_session;
	fabric->tf_ops.close_session = &tcm_loop_close_session;
	fabric->tf_ops.sess_get_index = &tcm_loop_sess_get_index;
	fabric->tf_ops.sess_get_initiator_sid = NULL;
	fabric->tf_ops.write_pending = &tcm_loop_write_pending;
	fabric->tf_ops.write_pending_status = &tcm_loop_write_pending_status;
	/*
	 * Not used for TCM loopback
	 */
	fabric->tf_ops.set_default_node_attributes =
					&tcm_loop_set_default_node_attributes;
	fabric->tf_ops.get_task_tag = &tcm_loop_get_task_tag;
	fabric->tf_ops.get_cmd_state = &tcm_loop_get_cmd_state;
	fabric->tf_ops.queue_data_in = &tcm_loop_queue_data_in;
	fabric->tf_ops.queue_status = &tcm_loop_queue_status;
	fabric->tf_ops.queue_tm_rsp = &tcm_loop_queue_tm_rsp;

	/*
	 * Setup function pointers for generic logic in target_core_fabric_configfs.c
	 */
	fabric->tf_ops.fabric_make_wwn = &tcm_loop_make_scsi_hba;
	fabric->tf_ops.fabric_drop_wwn = &tcm_loop_drop_scsi_hba;
	fabric->tf_ops.fabric_make_tpg = &tcm_loop_make_naa_tpg;
	fabric->tf_ops.fabric_drop_tpg = &tcm_loop_drop_naa_tpg;
	/*
	 * fabric_post_link() and fabric_pre_unlink() are used for
	 * registration and release of TCM Loop Virtual SCSI LUNs.
	 */
	fabric->tf_ops.fabric_post_link = &tcm_loop_port_link;
	fabric->tf_ops.fabric_pre_unlink = &tcm_loop_port_unlink;
	fabric->tf_ops.fabric_make_np = NULL;
	fabric->tf_ops.fabric_drop_np = NULL;
	/*
	 * Setup default attribute lists for various fabric->tf_cit_tmpl
	 */
	TF_CIT_TMPL(fabric)->tfc_wwn_cit.ct_attrs = tcm_loop_wwn_attrs;
	TF_CIT_TMPL(fabric)->tfc_tpg_base_cit.ct_attrs = tcm_loop_tpg_attrs;
	TF_CIT_TMPL(fabric)->tfc_tpg_attrib_cit.ct_attrs = NULL;
	TF_CIT_TMPL(fabric)->tfc_tpg_param_cit.ct_attrs = NULL;
	TF_CIT_TMPL(fabric)->tfc_tpg_np_base_cit.ct_attrs = NULL;
	/*
	 * Once fabric->tf_ops has been setup, now register the fabric for
	 * use within TCM
	 */
	ret = target_fabric_configfs_register(fabric);
	if (ret < 0) {
		pr_err("target_fabric_configfs_register() for"
				" TCM_Loop failed!\n");
		target_fabric_configfs_free(fabric);
		return -1;
	}
	/*
	 * Setup our local pointer to *fabric.
	 */
	tcm_loop_fabric_configfs = fabric;
	pr_debug("TCM_LOOP[0] - Set fabric ->"
			" tcm_loop_fabric_configfs\n");
	return 0;
}