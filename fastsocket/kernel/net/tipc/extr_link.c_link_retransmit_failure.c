#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* supported; char* acked; char* last_in; char* gap_after; char* gap_to; char* nack_sync; } ;
struct tipc_node {scalar_t__ addr; TYPE_2__ bclink; } ;
struct tipc_msg {int dummy; } ;
struct sk_buff {int dummy; } ;
struct link {scalar_t__ stale_count; TYPE_1__* owner; scalar_t__ addr; int /*<<< orphan*/  name; } ;
struct TYPE_6__ {scalar_t__ handle; } ;
struct TYPE_4__ {struct tipc_node* next; } ;
typedef  int /*<<< orphan*/  Handler ;

/* Variables and functions */
 int /*<<< orphan*/  TIPC_OUTPUT ; 
 TYPE_3__* TIPC_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  addr_string_fill (char*,scalar_t__) ; 
 struct tipc_msg* buf_msg (struct sk_buff*) ; 
 int /*<<< orphan*/  link_print (struct link*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ link_reset_all ; 
 char* msg_seqno (struct tipc_msg*) ; 
 int /*<<< orphan*/  tipc_k_signal (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  tipc_link_reset (struct link*) ; 
 int /*<<< orphan*/  tipc_msg_dbg (int /*<<< orphan*/ ,struct tipc_msg*,char*) ; 
 int /*<<< orphan*/  tipc_node_lock (struct tipc_node*) ; 
 int /*<<< orphan*/  tipc_node_unlock (struct tipc_node*) ; 
 int /*<<< orphan*/  tipc_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  warn (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void link_retransmit_failure(struct link *l_ptr, struct sk_buff *buf)
{
	struct tipc_msg *msg = buf_msg(buf);

	warn("Retransmission failure on link <%s>\n", l_ptr->name);
	tipc_msg_dbg(TIPC_OUTPUT, msg, ">RETR-FAIL>");

	if (l_ptr->addr) {

		/* Handle failure on standard link */

		link_print(l_ptr, TIPC_OUTPUT, "Resetting link\n");
		tipc_link_reset(l_ptr);

	} else {

		/* Handle failure on broadcast link */

		struct tipc_node *n_ptr;
		char addr_string[16];

		tipc_printf(TIPC_OUTPUT, "Msg seq number: %u,  ", msg_seqno(msg));
		tipc_printf(TIPC_OUTPUT, "Outstanding acks: %lu\n",
				     (unsigned long) TIPC_SKB_CB(buf)->handle);

		n_ptr = l_ptr->owner->next;
		tipc_node_lock(n_ptr);

		addr_string_fill(addr_string, n_ptr->addr);
		tipc_printf(TIPC_OUTPUT, "Multicast link info for %s\n", addr_string);
		tipc_printf(TIPC_OUTPUT, "Supported: %d,  ", n_ptr->bclink.supported);
		tipc_printf(TIPC_OUTPUT, "Acked: %u\n", n_ptr->bclink.acked);
		tipc_printf(TIPC_OUTPUT, "Last in: %u,  ", n_ptr->bclink.last_in);
		tipc_printf(TIPC_OUTPUT, "Gap after: %u,  ", n_ptr->bclink.gap_after);
		tipc_printf(TIPC_OUTPUT, "Gap to: %u\n", n_ptr->bclink.gap_to);
		tipc_printf(TIPC_OUTPUT, "Nack sync: %u\n\n", n_ptr->bclink.nack_sync);

		tipc_k_signal((Handler)link_reset_all, (unsigned long)n_ptr->addr);

		tipc_node_unlock(n_ptr);

		l_ptr->stale_count = 0;
	}
}