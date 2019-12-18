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
struct genl_info {int dummy; } ;

/* Variables and functions */
 int netlbl_domhsh_remove_default (struct netlbl_audit*) ; 
 int /*<<< orphan*/  netlbl_netlink_auditinfo (struct sk_buff*,struct netlbl_audit*) ; 

__attribute__((used)) static int netlbl_mgmt_removedef(struct sk_buff *skb, struct genl_info *info)
{
	struct netlbl_audit audit_info;

	netlbl_netlink_auditinfo(skb, &audit_info);

	return netlbl_domhsh_remove_default(&audit_info);
}