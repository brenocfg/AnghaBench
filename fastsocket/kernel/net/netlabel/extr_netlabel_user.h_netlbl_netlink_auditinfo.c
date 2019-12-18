#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct netlbl_audit {int /*<<< orphan*/  sessionid; int /*<<< orphan*/  loginuid; int /*<<< orphan*/  secid; } ;
struct TYPE_2__ {int /*<<< orphan*/  sessionid; int /*<<< orphan*/  loginuid; int /*<<< orphan*/  sid; } ;

/* Variables and functions */
 TYPE_1__ NETLINK_CB (struct sk_buff*) ; 

__attribute__((used)) static inline void netlbl_netlink_auditinfo(struct sk_buff *skb,
					    struct netlbl_audit *audit_info)
{
	audit_info->secid = NETLINK_CB(skb).sid;
	audit_info->loginuid = NETLINK_CB(skb).loginuid;
	audit_info->sessionid = NETLINK_CB(skb).sessionid;
}