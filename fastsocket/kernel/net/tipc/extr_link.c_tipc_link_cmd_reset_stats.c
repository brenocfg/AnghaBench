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
struct tipc_node {int dummy; } ;
struct sk_buff {int dummy; } ;
struct link {int dummy; } ;

/* Variables and functions */
 char* TIPC_CFG_TLV_ERROR ; 
 int /*<<< orphan*/  TIPC_TLV_LINK_NAME ; 
 int /*<<< orphan*/  TLV_CHECK (void const*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ TLV_DATA (void const*) ; 
 struct link* link_find_link (char*,struct tipc_node**) ; 
 int /*<<< orphan*/  link_reset_statistics (struct link*) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_bclink_name ; 
 scalar_t__ tipc_bclink_reset_stats () ; 
 struct sk_buff* tipc_cfg_reply_error_string (char*) ; 
 struct sk_buff* tipc_cfg_reply_none () ; 
 int /*<<< orphan*/  tipc_net_lock ; 
 int /*<<< orphan*/  tipc_node_lock (struct tipc_node*) ; 
 int /*<<< orphan*/  tipc_node_unlock (struct tipc_node*) ; 

struct sk_buff *tipc_link_cmd_reset_stats(const void *req_tlv_area, int req_tlv_space)
{
	char *link_name;
	struct link *l_ptr;
	struct tipc_node *node;

	if (!TLV_CHECK(req_tlv_area, req_tlv_space, TIPC_TLV_LINK_NAME))
		return tipc_cfg_reply_error_string(TIPC_CFG_TLV_ERROR);

	link_name = (char *)TLV_DATA(req_tlv_area);
	if (!strcmp(link_name, tipc_bclink_name)) {
		if (tipc_bclink_reset_stats())
			return tipc_cfg_reply_error_string("link not found");
		return tipc_cfg_reply_none();
	}

	read_lock_bh(&tipc_net_lock);
	l_ptr = link_find_link(link_name, &node);
	if (!l_ptr) {
		read_unlock_bh(&tipc_net_lock);
		return tipc_cfg_reply_error_string("link not found");
	}

	tipc_node_lock(node);
	link_reset_statistics(l_ptr);
	tipc_node_unlock(node);
	read_unlock_bh(&tipc_net_lock);
	return tipc_cfg_reply_none();
}