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
typedef  int /*<<< orphan*/  u32 ;
struct tipc_msg {int dummy; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;
struct bearer {TYPE_1__ publ; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSC_H_SIZE ; 
 int /*<<< orphan*/  LINK_CONFIG ; 
 struct sk_buff* buf_acquire (int /*<<< orphan*/ ) ; 
 struct tipc_msg* buf_msg (struct sk_buff*) ; 
 int /*<<< orphan*/  msg_init (struct tipc_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_bc_netid (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_dest_domain (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_media_addr (struct tipc_msg*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_set_non_seq (struct tipc_msg*,int) ; 
 int /*<<< orphan*/  msg_set_req_links (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_net_id ; 

__attribute__((used)) static struct sk_buff *tipc_disc_init_msg(u32 type,
					  u32 req_links,
					  u32 dest_domain,
					  struct bearer *b_ptr)
{
	struct sk_buff *buf = buf_acquire(DSC_H_SIZE);
	struct tipc_msg *msg;

	if (buf) {
		msg = buf_msg(buf);
		msg_init(msg, LINK_CONFIG, type, DSC_H_SIZE, dest_domain);
		msg_set_non_seq(msg, 1);
		msg_set_req_links(msg, req_links);
		msg_set_dest_domain(msg, dest_domain);
		msg_set_bc_netid(msg, tipc_net_id);
		msg_set_media_addr(msg, &b_ptr->publ.addr);
	}
	return buf;
}