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
struct nlattr {int dummy; } ;
struct iwl_test {int /*<<< orphan*/  trans; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_INFO (int /*<<< orphan*/ ,char*) ; 
 size_t IWL_TM_ATTR_COMMAND ; 
#define  IWL_TM_CMD_APP2DEV_BEGIN_TRACE 138 
#define  IWL_TM_CMD_APP2DEV_DIRECT_REG_READ32 137 
#define  IWL_TM_CMD_APP2DEV_DIRECT_REG_WRITE32 136 
#define  IWL_TM_CMD_APP2DEV_DIRECT_REG_WRITE8 135 
#define  IWL_TM_CMD_APP2DEV_END_TRACE 134 
#define  IWL_TM_CMD_APP2DEV_GET_DEVICE_ID 133 
#define  IWL_TM_CMD_APP2DEV_GET_FW_VERSION 132 
#define  IWL_TM_CMD_APP2DEV_INDIRECT_BUFFER_READ 131 
#define  IWL_TM_CMD_APP2DEV_INDIRECT_BUFFER_WRITE 130 
#define  IWL_TM_CMD_APP2DEV_NOTIFICATIONS 129 
#define  IWL_TM_CMD_APP2DEV_UCODE 128 
 int iwl_test_fw_cmd (struct iwl_test*,struct nlattr**) ; 
 int iwl_test_get_dev_id (struct iwl_test*,struct nlattr**) ; 
 int iwl_test_get_fw_ver (struct iwl_test*,struct nlattr**) ; 
 int iwl_test_indirect_mem (struct iwl_test*,struct nlattr**) ; 
 int iwl_test_notifications (struct iwl_test*,struct nlattr**) ; 
 int iwl_test_reg (struct iwl_test*,struct nlattr**) ; 
 int iwl_test_trace_begin (struct iwl_test*,struct nlattr**) ; 
 int /*<<< orphan*/  iwl_test_trace_stop (struct iwl_test*) ; 
 int nla_get_u32 (struct nlattr*) ; 

int iwl_test_handle_cmd(struct iwl_test *tst, struct nlattr **tb)
{
	int result;

	switch (nla_get_u32(tb[IWL_TM_ATTR_COMMAND])) {
	case IWL_TM_CMD_APP2DEV_UCODE:
		IWL_DEBUG_INFO(tst->trans, "test cmd to uCode\n");
		result = iwl_test_fw_cmd(tst, tb);
		break;

	case IWL_TM_CMD_APP2DEV_DIRECT_REG_READ32:
	case IWL_TM_CMD_APP2DEV_DIRECT_REG_WRITE32:
	case IWL_TM_CMD_APP2DEV_DIRECT_REG_WRITE8:
		IWL_DEBUG_INFO(tst->trans, "test cmd to register\n");
		result = iwl_test_reg(tst, tb);
		break;

	case IWL_TM_CMD_APP2DEV_BEGIN_TRACE:
		IWL_DEBUG_INFO(tst->trans, "test uCode trace cmd to driver\n");
		result = iwl_test_trace_begin(tst, tb);
		break;

	case IWL_TM_CMD_APP2DEV_END_TRACE:
		iwl_test_trace_stop(tst);
		result = 0;
		break;

	case IWL_TM_CMD_APP2DEV_INDIRECT_BUFFER_READ:
	case IWL_TM_CMD_APP2DEV_INDIRECT_BUFFER_WRITE:
		IWL_DEBUG_INFO(tst->trans, "test indirect memory cmd\n");
		result = iwl_test_indirect_mem(tst, tb);
		break;

	case IWL_TM_CMD_APP2DEV_NOTIFICATIONS:
		IWL_DEBUG_INFO(tst->trans, "test notifications cmd\n");
		result = iwl_test_notifications(tst, tb);
		break;

	case IWL_TM_CMD_APP2DEV_GET_FW_VERSION:
		IWL_DEBUG_INFO(tst->trans, "test get FW ver cmd\n");
		result = iwl_test_get_fw_ver(tst, tb);
		break;

	case IWL_TM_CMD_APP2DEV_GET_DEVICE_ID:
		IWL_DEBUG_INFO(tst->trans, "test Get device ID cmd\n");
		result = iwl_test_get_dev_id(tst, tb);
		break;

	default:
		IWL_DEBUG_INFO(tst->trans, "Unknown test command\n");
		result = 1;
		break;
	}
	return result;
}