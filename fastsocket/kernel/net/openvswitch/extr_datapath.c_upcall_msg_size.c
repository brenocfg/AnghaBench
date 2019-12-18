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
struct sk_buff {int /*<<< orphan*/  len; } ;
struct ovs_header {int dummy; } ;
struct nlattr {int /*<<< orphan*/  nla_len; } ;

/* Variables and functions */
 scalar_t__ NLA_ALIGN (int /*<<< orphan*/ ) ; 
 size_t NLMSG_ALIGN (int) ; 
 int /*<<< orphan*/  key_attr_size () ; 
 size_t nla_total_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t upcall_msg_size(const struct sk_buff *skb,
			      const struct nlattr *userdata)
{
	size_t size = NLMSG_ALIGN(sizeof(struct ovs_header))
		+ nla_total_size(skb->len) /* OVS_PACKET_ATTR_PACKET */
		+ nla_total_size(key_attr_size()); /* OVS_PACKET_ATTR_KEY */

	/* OVS_PACKET_ATTR_USERDATA */
	if (userdata)
		size += NLA_ALIGN(userdata->nla_len);

	return size;
}