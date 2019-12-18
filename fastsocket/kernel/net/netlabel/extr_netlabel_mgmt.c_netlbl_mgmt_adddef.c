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
struct sk_buff {int dummy; } ;
struct netlbl_audit {int dummy; } ;
struct genl_info {int /*<<< orphan*/ ** attrs; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t NLBL_MGMT_A_IPV4ADDR ; 
 size_t NLBL_MGMT_A_IPV4MASK ; 
 size_t NLBL_MGMT_A_IPV6ADDR ; 
 size_t NLBL_MGMT_A_IPV6MASK ; 
 size_t NLBL_MGMT_A_PROTOCOL ; 
 int netlbl_mgmt_add_common (struct genl_info*,struct netlbl_audit*) ; 
 int /*<<< orphan*/  netlbl_netlink_auditinfo (struct sk_buff*,struct netlbl_audit*) ; 

__attribute__((used)) static int netlbl_mgmt_adddef(struct sk_buff *skb, struct genl_info *info)
{
	struct netlbl_audit audit_info;

	if ((!info->attrs[NLBL_MGMT_A_PROTOCOL]) ||
	    (info->attrs[NLBL_MGMT_A_IPV4ADDR] &&
	     info->attrs[NLBL_MGMT_A_IPV6ADDR]) ||
	    (info->attrs[NLBL_MGMT_A_IPV4MASK] &&
	     info->attrs[NLBL_MGMT_A_IPV6MASK]) ||
	    ((info->attrs[NLBL_MGMT_A_IPV4ADDR] != NULL) ^
	     (info->attrs[NLBL_MGMT_A_IPV4MASK] != NULL)) ||
	    ((info->attrs[NLBL_MGMT_A_IPV6ADDR] != NULL) ^
	     (info->attrs[NLBL_MGMT_A_IPV6MASK] != NULL)))
		return -EINVAL;

	netlbl_netlink_auditinfo(skb, &audit_info);

	return netlbl_mgmt_add_common(info, &audit_info);
}