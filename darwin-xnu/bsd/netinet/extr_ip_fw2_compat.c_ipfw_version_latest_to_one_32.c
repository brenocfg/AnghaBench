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
struct ip_fw_compat_32 {int /*<<< orphan*/  timestamp; int /*<<< orphan*/  fw_bcnt; int /*<<< orphan*/  fw_pcnt; int /*<<< orphan*/  fw_number; int /*<<< orphan*/  context; int /*<<< orphan*/  version; } ;
struct ip_fw_32 {int /*<<< orphan*/  timestamp; int /*<<< orphan*/  bcnt; int /*<<< orphan*/  pcnt; int /*<<< orphan*/  rulenum; int /*<<< orphan*/  context; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAST_DOWN_EXPLICIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IP_FW_VERSION_1 ; 
 int /*<<< orphan*/  bzero (struct ip_fw_compat_32*,int) ; 
 int /*<<< orphan*/  ipfw_map_from_actions_32 (struct ip_fw_32*,struct ip_fw_compat_32*) ; 
 int /*<<< orphan*/  ipfw_map_from_cmds_32 (struct ip_fw_32*,struct ip_fw_compat_32*) ; 
 int /*<<< orphan*/  ipfw_print_vers1_struct_32 (struct ip_fw_compat_32*) ; 
 int /*<<< orphan*/  user32_addr_t ; 

__attribute__((used)) static void
ipfw_version_latest_to_one_32(struct ip_fw_32 *curr_rule, struct ip_fw_compat_32 *rule_vers1)
{
	if (!rule_vers1)
		return;
		
	bzero(rule_vers1, sizeof(struct ip_fw_compat_32));
	
	rule_vers1->version = IP_FW_VERSION_1;
	rule_vers1->context = CAST_DOWN_EXPLICIT(user32_addr_t,curr_rule->context);
	rule_vers1->fw_number = curr_rule->rulenum;
	rule_vers1->fw_pcnt = curr_rule->pcnt;
	rule_vers1->fw_bcnt = curr_rule->bcnt;
	rule_vers1->timestamp = curr_rule->timestamp;
	
	/* convert actions */
	ipfw_map_from_actions_32(curr_rule, rule_vers1);

	/* convert commands */
	ipfw_map_from_cmds_32(curr_rule, rule_vers1);
	
#if FW2_DEBUG_VERBOSE
	ipfw_print_vers1_struct_32(rule_vers1);
#endif
}