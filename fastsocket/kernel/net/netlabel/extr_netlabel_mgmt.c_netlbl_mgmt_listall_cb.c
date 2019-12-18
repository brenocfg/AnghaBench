#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct netlbl_domhsh_walk_arg {int /*<<< orphan*/  skb; int /*<<< orphan*/  seq; TYPE_1__* nl_cb; } ;
struct netlbl_dom_map {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  pid; } ;
struct TYPE_3__ {int /*<<< orphan*/  skb; } ;

/* Variables and functions */
 int ENOMEM ; 
 TYPE_2__ NETLINK_CB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NLBL_MGMT_C_LISTALL ; 
 int /*<<< orphan*/  NLM_F_MULTI ; 
 int /*<<< orphan*/  genlmsg_cancel (int /*<<< orphan*/ ,void*) ; 
 int genlmsg_end (int /*<<< orphan*/ ,void*) ; 
 void* genlmsg_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netlbl_mgmt_gnl_family ; 
 int netlbl_mgmt_listentry (int /*<<< orphan*/ ,struct netlbl_dom_map*) ; 

__attribute__((used)) static int netlbl_mgmt_listall_cb(struct netlbl_dom_map *entry, void *arg)
{
	int ret_val = -ENOMEM;
	struct netlbl_domhsh_walk_arg *cb_arg = arg;
	void *data;

	data = genlmsg_put(cb_arg->skb, NETLINK_CB(cb_arg->nl_cb->skb).pid,
			   cb_arg->seq, &netlbl_mgmt_gnl_family,
			   NLM_F_MULTI, NLBL_MGMT_C_LISTALL);
	if (data == NULL)
		goto listall_cb_failure;

	ret_val = netlbl_mgmt_listentry(cb_arg->skb, entry);
	if (ret_val != 0)
		goto listall_cb_failure;

	cb_arg->seq++;
	return genlmsg_end(cb_arg->skb, data);

listall_cb_failure:
	genlmsg_cancel(cb_arg->skb, data);
	return ret_val;
}