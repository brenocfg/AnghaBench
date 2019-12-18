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
struct client_update_ramrod_data {void* silent_vlan_mask; void* silent_vlan_value; void* silent_vlan_removal_flg; void* silent_vlan_change_flg; void* default_vlan_change_flg; void* default_vlan_enable_flg; void* activate_change_flg; void* activate_flg; void* anti_spoofing_change_flg; void* anti_spoofing_enable_flg; void* outer_vlan_removal_change_flg; void* outer_vlan_removal_enable_flg; void* inner_vlan_removal_change_flg; void* inner_vlan_removal_enable_flg; void* default_vlan; int /*<<< orphan*/  func_id; int /*<<< orphan*/  client_id; } ;
struct bnx2x_queue_update_params {int /*<<< orphan*/  silent_removal_mask; int /*<<< orphan*/  silent_removal_value; int /*<<< orphan*/  update_flags; int /*<<< orphan*/  def_vlan; } ;
struct bnx2x_queue_sp_obj {int /*<<< orphan*/  func_id; int /*<<< orphan*/  cl_id; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_Q_UPDATE_ACTIVATE ; 
 int /*<<< orphan*/  BNX2X_Q_UPDATE_ACTIVATE_CHNG ; 
 int /*<<< orphan*/  BNX2X_Q_UPDATE_ANTI_SPOOF ; 
 int /*<<< orphan*/  BNX2X_Q_UPDATE_ANTI_SPOOF_CHNG ; 
 int /*<<< orphan*/  BNX2X_Q_UPDATE_DEF_VLAN_EN ; 
 int /*<<< orphan*/  BNX2X_Q_UPDATE_DEF_VLAN_EN_CHNG ; 
 int /*<<< orphan*/  BNX2X_Q_UPDATE_IN_VLAN_REM ; 
 int /*<<< orphan*/  BNX2X_Q_UPDATE_IN_VLAN_REM_CHNG ; 
 int /*<<< orphan*/  BNX2X_Q_UPDATE_OUT_VLAN_REM ; 
 int /*<<< orphan*/  BNX2X_Q_UPDATE_OUT_VLAN_REM_CHNG ; 
 int /*<<< orphan*/  BNX2X_Q_UPDATE_SILENT_VLAN_REM ; 
 int /*<<< orphan*/  BNX2X_Q_UPDATE_SILENT_VLAN_REM_CHNG ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 void* test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bnx2x_q_fill_update_data(struct bnx2x *bp,
				     struct bnx2x_queue_sp_obj *obj,
				     struct bnx2x_queue_update_params *params,
				     struct client_update_ramrod_data *data)
{
	/* Client ID of the client to update */
	data->client_id = obj->cl_id;

	/* Function ID of the client to update */
	data->func_id = obj->func_id;

	/* Default VLAN value */
	data->default_vlan = cpu_to_le16(params->def_vlan);

	/* Inner VLAN stripping */
	data->inner_vlan_removal_enable_flg =
		test_bit(BNX2X_Q_UPDATE_IN_VLAN_REM, &params->update_flags);
	data->inner_vlan_removal_change_flg =
		test_bit(BNX2X_Q_UPDATE_IN_VLAN_REM_CHNG,
			 &params->update_flags);

	/* Outer VLAN stripping */
	data->outer_vlan_removal_enable_flg =
		test_bit(BNX2X_Q_UPDATE_OUT_VLAN_REM, &params->update_flags);
	data->outer_vlan_removal_change_flg =
		test_bit(BNX2X_Q_UPDATE_OUT_VLAN_REM_CHNG,
			 &params->update_flags);

	/* Drop packets that have source MAC that doesn't belong to this
	 * Queue.
	 */
	data->anti_spoofing_enable_flg =
		test_bit(BNX2X_Q_UPDATE_ANTI_SPOOF, &params->update_flags);
	data->anti_spoofing_change_flg =
		test_bit(BNX2X_Q_UPDATE_ANTI_SPOOF_CHNG, &params->update_flags);

	/* Activate/Deactivate */
	data->activate_flg =
		test_bit(BNX2X_Q_UPDATE_ACTIVATE, &params->update_flags);
	data->activate_change_flg =
		test_bit(BNX2X_Q_UPDATE_ACTIVATE_CHNG, &params->update_flags);

	/* Enable default VLAN */
	data->default_vlan_enable_flg =
		test_bit(BNX2X_Q_UPDATE_DEF_VLAN_EN, &params->update_flags);
	data->default_vlan_change_flg =
		test_bit(BNX2X_Q_UPDATE_DEF_VLAN_EN_CHNG,
			 &params->update_flags);

	/* silent vlan removal */
	data->silent_vlan_change_flg =
		test_bit(BNX2X_Q_UPDATE_SILENT_VLAN_REM_CHNG,
			 &params->update_flags);
	data->silent_vlan_removal_flg =
		test_bit(BNX2X_Q_UPDATE_SILENT_VLAN_REM, &params->update_flags);
	data->silent_vlan_value = cpu_to_le16(params->silent_removal_value);
	data->silent_vlan_mask = cpu_to_le16(params->silent_removal_mask);
}