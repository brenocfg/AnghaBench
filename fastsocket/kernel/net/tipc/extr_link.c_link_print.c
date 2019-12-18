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
typedef  scalar_t__ u32 ;
struct print_buf {int dummy; } ;
struct link {int out_queue_size; scalar_t__ deferred_inqueue_sz; TYPE_3__* newest_deferred_in; TYPE_3__* oldest_deferred_in; TYPE_3__* last_out; TYPE_3__* next_out; TYPE_3__* first_out; scalar_t__ next_in_no; scalar_t__ next_out_no; TYPE_2__* b_ptr; int /*<<< orphan*/  addr; } ;
struct TYPE_6__ {int /*<<< orphan*/ * next; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct TYPE_5__ {TYPE_1__ publ; } ;

/* Variables and functions */
 int /*<<< orphan*/  buf_msg (TYPE_3__*) ; 
 int /*<<< orphan*/  link_dump_send_queue (struct link*) ; 
 scalar_t__ link_reset_reset (struct link*) ; 
 scalar_t__ link_reset_unknown (struct link*) ; 
 scalar_t__ link_working_unknown (struct link*) ; 
 scalar_t__ link_working_working (struct link*) ; 
 scalar_t__ mod (scalar_t__) ; 
 scalar_t__ msg_seqno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_printf (struct print_buf*,char const*,...) ; 

__attribute__((used)) static void link_print(struct link *l_ptr, struct print_buf *buf,
		       const char *str)
{
	tipc_printf(buf, str);
	if (link_reset_reset(l_ptr) || link_reset_unknown(l_ptr))
		return;
	tipc_printf(buf, "Link %x<%s>:",
		    l_ptr->addr, l_ptr->b_ptr->publ.name);
	tipc_printf(buf, ": NXO(%u):", mod(l_ptr->next_out_no));
	tipc_printf(buf, "NXI(%u):", mod(l_ptr->next_in_no));
	tipc_printf(buf, "SQUE");
	if (l_ptr->first_out) {
		tipc_printf(buf, "[%u..", msg_seqno(buf_msg(l_ptr->first_out)));
		if (l_ptr->next_out)
			tipc_printf(buf, "%u..",
				    msg_seqno(buf_msg(l_ptr->next_out)));
		tipc_printf(buf, "%u]",
			    msg_seqno(buf_msg
				      (l_ptr->last_out)), l_ptr->out_queue_size);
		if ((mod(msg_seqno(buf_msg(l_ptr->last_out)) -
			 msg_seqno(buf_msg(l_ptr->first_out)))
		     != (l_ptr->out_queue_size - 1))
		    || (l_ptr->last_out->next != NULL)) {
			tipc_printf(buf, "\nSend queue inconsistency\n");
			tipc_printf(buf, "first_out= %x ", l_ptr->first_out);
			tipc_printf(buf, "next_out= %x ", l_ptr->next_out);
			tipc_printf(buf, "last_out= %x ", l_ptr->last_out);
			link_dump_send_queue(l_ptr);
		}
	} else
		tipc_printf(buf, "[]");
	tipc_printf(buf, "SQSIZ(%u)", l_ptr->out_queue_size);
	if (l_ptr->oldest_deferred_in) {
		u32 o = msg_seqno(buf_msg(l_ptr->oldest_deferred_in));
		u32 n = msg_seqno(buf_msg(l_ptr->newest_deferred_in));
		tipc_printf(buf, ":RQUE[%u..%u]", o, n);
		if (l_ptr->deferred_inqueue_sz != mod((n + 1) - o)) {
			tipc_printf(buf, ":RQSIZ(%u)",
				    l_ptr->deferred_inqueue_sz);
		}
	}
	if (link_working_unknown(l_ptr))
		tipc_printf(buf, ":WU");
	if (link_reset_reset(l_ptr))
		tipc_printf(buf, ":RR");
	if (link_reset_unknown(l_ptr))
		tipc_printf(buf, ":RU");
	if (link_working_working(l_ptr))
		tipc_printf(buf, ":WW");
	tipc_printf(buf, "\n");
}