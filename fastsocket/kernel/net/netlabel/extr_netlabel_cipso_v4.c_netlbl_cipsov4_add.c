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
struct genl_info {int /*<<< orphan*/ * attrs; } ;

/* Variables and functions */
#define  CIPSO_V4_MAP_LOCAL 130 
#define  CIPSO_V4_MAP_PASS 129 
#define  CIPSO_V4_MAP_TRANS 128 
 int EINVAL ; 
 size_t NLBL_CIPSOV4_A_DOI ; 
 size_t NLBL_CIPSOV4_A_MTYPE ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netlabel_mgmt_protocount ; 
 int netlbl_cipsov4_add_local (struct genl_info*,struct netlbl_audit*) ; 
 int netlbl_cipsov4_add_pass (struct genl_info*,struct netlbl_audit*) ; 
 int netlbl_cipsov4_add_std (struct genl_info*,struct netlbl_audit*) ; 
 int /*<<< orphan*/  netlbl_netlink_auditinfo (struct sk_buff*,struct netlbl_audit*) ; 
 int nla_get_u32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int netlbl_cipsov4_add(struct sk_buff *skb, struct genl_info *info)

{
	int ret_val = -EINVAL;
	const char *type_str = "(unknown)";
	struct netlbl_audit audit_info;

	if (!info->attrs[NLBL_CIPSOV4_A_DOI] ||
	    !info->attrs[NLBL_CIPSOV4_A_MTYPE])
		return -EINVAL;

	netlbl_netlink_auditinfo(skb, &audit_info);
	switch (nla_get_u32(info->attrs[NLBL_CIPSOV4_A_MTYPE])) {
	case CIPSO_V4_MAP_TRANS:
		type_str = "trans";
		ret_val = netlbl_cipsov4_add_std(info, &audit_info);
		break;
	case CIPSO_V4_MAP_PASS:
		type_str = "pass";
		ret_val = netlbl_cipsov4_add_pass(info, &audit_info);
		break;
	case CIPSO_V4_MAP_LOCAL:
		type_str = "local";
		ret_val = netlbl_cipsov4_add_local(info, &audit_info);
		break;
	}
	if (ret_val == 0)
		atomic_inc(&netlabel_mgmt_protocount);

	return ret_val;
}