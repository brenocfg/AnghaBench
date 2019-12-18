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
struct sk_buff {int dummy; } ;
struct netlbl_audit {int dummy; } ;
struct genl_info {int /*<<< orphan*/ * attrs; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t NLBL_UNLABEL_A_IPV4ADDR ; 
 size_t NLBL_UNLABEL_A_IPV4MASK ; 
 size_t NLBL_UNLABEL_A_IPV6ADDR ; 
 size_t NLBL_UNLABEL_A_IPV6MASK ; 
 size_t NLBL_UNLABEL_A_SECCTX ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  netlbl_netlink_auditinfo (struct sk_buff*,struct netlbl_audit*) ; 
 int netlbl_unlabel_addrinfo_get (struct genl_info*,void**,void**,int /*<<< orphan*/ *) ; 
 int netlbl_unlhsh_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct netlbl_audit*) ; 
 int /*<<< orphan*/  nla_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_len (int /*<<< orphan*/ ) ; 
 int security_secctx_to_secid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int netlbl_unlabel_staticadddef(struct sk_buff *skb,
				       struct genl_info *info)
{
	int ret_val;
	void *addr;
	void *mask;
	u32 addr_len;
	u32 secid;
	struct netlbl_audit audit_info;

	/* Don't allow users to add both IPv4 and IPv6 addresses for a
	 * single entry.  However, allow users to create two entries, one each
	 * for IPv4 and IPv6, with the same LSM security context which should
	 * achieve the same result. */
	if (!info->attrs[NLBL_UNLABEL_A_SECCTX] ||
	    !((!info->attrs[NLBL_UNLABEL_A_IPV4ADDR] ||
	       !info->attrs[NLBL_UNLABEL_A_IPV4MASK]) ^
	      (!info->attrs[NLBL_UNLABEL_A_IPV6ADDR] ||
	       !info->attrs[NLBL_UNLABEL_A_IPV6MASK])))
		return -EINVAL;

	netlbl_netlink_auditinfo(skb, &audit_info);

	ret_val = netlbl_unlabel_addrinfo_get(info, &addr, &mask, &addr_len);
	if (ret_val != 0)
		return ret_val;
	ret_val = security_secctx_to_secid(
		                  nla_data(info->attrs[NLBL_UNLABEL_A_SECCTX]),
				  nla_len(info->attrs[NLBL_UNLABEL_A_SECCTX]),
				  &secid);
	if (ret_val != 0)
		return ret_val;

	return netlbl_unlhsh_add(&init_net,
				 NULL, addr, mask, addr_len, secid,
				 &audit_info);
}