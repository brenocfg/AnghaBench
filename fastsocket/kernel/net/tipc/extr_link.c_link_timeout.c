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
typedef  int u32 ;
struct tipc_msg {int dummy; } ;
struct TYPE_2__ {scalar_t__ max_queue_sz; int msg_lengths_total; int /*<<< orphan*/ * msg_length_profile; int /*<<< orphan*/  msg_length_counts; int /*<<< orphan*/  queue_sz_counts; int /*<<< orphan*/  accu_queue_sz; } ;
struct link {scalar_t__ out_queue_size; int /*<<< orphan*/  owner; scalar_t__ next_out; TYPE_1__ stats; scalar_t__ first_out; } ;

/* Variables and functions */
 scalar_t__ FIRST_FRAGMENT ; 
 scalar_t__ MSG_FRAGMENTER ; 
 int /*<<< orphan*/  TIMEOUT_EVT ; 
 struct tipc_msg* buf_msg (scalar_t__) ; 
 int /*<<< orphan*/  link_check_defragm_bufs (struct link*) ; 
 int /*<<< orphan*/  link_state_event (struct link*,int /*<<< orphan*/ ) ; 
 struct tipc_msg* msg_get_wrapped (struct tipc_msg*) ; 
 int msg_size (struct tipc_msg*) ; 
 scalar_t__ msg_type (struct tipc_msg*) ; 
 scalar_t__ msg_user (struct tipc_msg*) ; 
 int /*<<< orphan*/  tipc_link_push_queue (struct link*) ; 
 int /*<<< orphan*/  tipc_node_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_node_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void link_timeout(struct link *l_ptr)
{
	tipc_node_lock(l_ptr->owner);

	/* update counters used in statistical profiling of send traffic */

	l_ptr->stats.accu_queue_sz += l_ptr->out_queue_size;
	l_ptr->stats.queue_sz_counts++;

	if (l_ptr->out_queue_size > l_ptr->stats.max_queue_sz)
		l_ptr->stats.max_queue_sz = l_ptr->out_queue_size;

	if (l_ptr->first_out) {
		struct tipc_msg *msg = buf_msg(l_ptr->first_out);
		u32 length = msg_size(msg);

		if ((msg_user(msg) == MSG_FRAGMENTER)
		    && (msg_type(msg) == FIRST_FRAGMENT)) {
			length = msg_size(msg_get_wrapped(msg));
		}
		if (length) {
			l_ptr->stats.msg_lengths_total += length;
			l_ptr->stats.msg_length_counts++;
			if (length <= 64)
				l_ptr->stats.msg_length_profile[0]++;
			else if (length <= 256)
				l_ptr->stats.msg_length_profile[1]++;
			else if (length <= 1024)
				l_ptr->stats.msg_length_profile[2]++;
			else if (length <= 4096)
				l_ptr->stats.msg_length_profile[3]++;
			else if (length <= 16384)
				l_ptr->stats.msg_length_profile[4]++;
			else if (length <= 32768)
				l_ptr->stats.msg_length_profile[5]++;
			else
				l_ptr->stats.msg_length_profile[6]++;
		}
	}

	/* do all other link processing performed on a periodic basis */

	link_check_defragm_bufs(l_ptr);

	link_state_event(l_ptr, TIMEOUT_EVT);

	if (l_ptr->next_out)
		tipc_link_push_queue(l_ptr);

	tipc_node_unlock(l_ptr->owner);
}