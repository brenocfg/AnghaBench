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
typedef  int u_int32_t ;
struct ip_old_fw {int dummy; } ;
struct ip_fw_compat_64 {int dummy; } ;
struct ip_fw_compat_32 {int dummy; } ;
struct ip_fw_64 {int dummy; } ;
struct ip_fw_32 {int dummy; } ;
struct ip_fw {int dummy; } ;

/* Variables and functions */
#define  IP_FW_CURRENT_API_VERSION 130 
#define  IP_FW_VERSION_0 129 
#define  IP_FW_VERSION_1 128 
 int /*<<< orphan*/  ipfw_version_latest_to_one_32 (struct ip_fw_32*,struct ip_fw_compat_32*) ; 
 int /*<<< orphan*/  ipfw_version_latest_to_one_64 (struct ip_fw_64*,struct ip_fw_compat_64*) ; 
 int /*<<< orphan*/  ipfw_version_latest_to_zero (struct ip_fw*,struct ip_old_fw*,int) ; 

void
ipfw_convert_from_latest(struct ip_fw *curr_rule, void *old_rule, u_int32_t api_version, int is64user)
{
	switch (api_version) {
		case IP_FW_VERSION_0:
		{
			struct ip_old_fw	*rule_vers0 = old_rule;
			
			ipfw_version_latest_to_zero(curr_rule, rule_vers0, is64user);
			break;
		}
		case IP_FW_VERSION_1:
		{			
			if ( is64user )
				ipfw_version_latest_to_one_64((struct ip_fw_64*)curr_rule, (struct ip_fw_compat_64 *)old_rule);
			else
				ipfw_version_latest_to_one_32((struct ip_fw_32*)curr_rule, (struct ip_fw_compat_32 *)old_rule);

			break;
		}
		case IP_FW_CURRENT_API_VERSION:
			/* ipfw2 for now, don't need to do anything */
			break;
		
		default:
			/* unknown version */
			break;
	}
}