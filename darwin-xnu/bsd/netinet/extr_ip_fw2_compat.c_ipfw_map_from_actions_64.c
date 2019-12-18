#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  sin_addr; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; int /*<<< orphan*/  sin_len; } ;
struct ip_fw_compat_64 {int /*<<< orphan*/  fw_flg; int /*<<< orphan*/  fw_reject_code_compat; TYPE_1__ fw_fwd_ip_compat; int /*<<< orphan*/  fw_divert_port_compat; int /*<<< orphan*/  fw_skipto_rule_compat; } ;
struct ip_fw_64 {int cmd_len; int act_ofs; } ;
struct TYPE_8__ {int /*<<< orphan*/  sin_addr; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; int /*<<< orphan*/  sin_len; } ;
struct TYPE_9__ {TYPE_2__ sa; } ;
typedef  TYPE_3__ ipfw_insn_sa ;
struct TYPE_10__ {int opcode; int /*<<< orphan*/  arg1; } ;
typedef  TYPE_4__ ipfw_insn ;

/* Variables and functions */
 TYPE_4__* ACTION_PTR (struct ip_fw_64*) ; 
 scalar_t__ F_LEN (TYPE_4__*) ; 
 int /*<<< orphan*/  IP_FW_F_ACCEPT_COMPAT ; 
 int /*<<< orphan*/  IP_FW_F_CHECK_S_COMPAT ; 
 int /*<<< orphan*/  IP_FW_F_COUNT_COMPAT ; 
 int /*<<< orphan*/  IP_FW_F_DENY_COMPAT ; 
 int /*<<< orphan*/  IP_FW_F_DIVERT_COMPAT ; 
 int /*<<< orphan*/  IP_FW_F_FWD_COMPAT ; 
 int /*<<< orphan*/  IP_FW_F_PIPE_COMPAT ; 
 int /*<<< orphan*/  IP_FW_F_QUEUE_COMPAT ; 
 int /*<<< orphan*/  IP_FW_F_REJECT_COMPAT ; 
 int /*<<< orphan*/  IP_FW_F_SKIPTO_COMPAT ; 
 int /*<<< orphan*/  IP_FW_F_TEE_COMPAT ; 
#define  O_ACCEPT 138 
#define  O_CHECK_STATE 137 
#define  O_COUNT 136 
#define  O_DENY 135 
#define  O_DIVERT 134 
#define  O_FORWARD_IP 133 
#define  O_PIPE 132 
#define  O_QUEUE 131 
#define  O_REJECT 130 
#define  O_SKIPTO 129 
#define  O_TEE 128 

__attribute__((used)) static void
ipfw_map_from_actions_64(struct ip_fw_64 *curr_rule, struct ip_fw_compat_64 *compat_rule)
{
	int l;
	ipfw_insn	*cmd;
	for (l = curr_rule->cmd_len - curr_rule->act_ofs, cmd = ACTION_PTR(curr_rule);
			l > 0 ; 
			l -= F_LEN(cmd), cmd += F_LEN(cmd)) {
		switch (cmd->opcode) {
			case O_ACCEPT:
				compat_rule->fw_flg |= IP_FW_F_ACCEPT_COMPAT;
				break;
			case O_COUNT:
				compat_rule->fw_flg |= IP_FW_F_COUNT_COMPAT;
				break;
			case O_PIPE:
				compat_rule->fw_flg |= IP_FW_F_PIPE_COMPAT;
				compat_rule->fw_divert_port_compat = cmd->arg1;
				break;
			case O_QUEUE:
				compat_rule->fw_flg |= IP_FW_F_QUEUE_COMPAT;
				compat_rule->fw_divert_port_compat = cmd->arg1;
				break;
			case O_SKIPTO:
				compat_rule->fw_flg |= IP_FW_F_SKIPTO_COMPAT;
				compat_rule->fw_skipto_rule_compat = cmd->arg1;
				break;
			case O_DIVERT:
				compat_rule->fw_flg |= IP_FW_F_DIVERT_COMPAT;
				compat_rule->fw_divert_port_compat = cmd->arg1;
				break;
			case O_TEE:
				compat_rule->fw_flg |= IP_FW_F_TEE_COMPAT;
				compat_rule->fw_divert_port_compat = cmd->arg1;
				break;
			case O_FORWARD_IP:
			{
				ipfw_insn_sa	*p = (ipfw_insn_sa *)cmd;
				
				compat_rule->fw_flg |= IP_FW_F_FWD_COMPAT;
				compat_rule->fw_fwd_ip_compat.sin_len = p->sa.sin_len;
				compat_rule->fw_fwd_ip_compat.sin_family = p->sa.sin_family;
				compat_rule->fw_fwd_ip_compat.sin_port = p->sa.sin_port;
				compat_rule->fw_fwd_ip_compat.sin_addr = p->sa.sin_addr;

				break;
			}
			case O_DENY:
				compat_rule->fw_flg |= IP_FW_F_DENY_COMPAT;
				break;
			case O_REJECT:
				compat_rule->fw_flg |= IP_FW_F_REJECT_COMPAT;
				compat_rule->fw_reject_code_compat = cmd->arg1;
				break;
			case O_CHECK_STATE:
				compat_rule->fw_flg |= IP_FW_F_CHECK_S_COMPAT;
				break;
			default:
				break;
		}
	}
}