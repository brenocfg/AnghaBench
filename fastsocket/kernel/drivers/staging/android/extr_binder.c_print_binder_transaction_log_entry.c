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
struct binder_transaction_log_entry {int debug_id; int call_type; int from_proc; int from_thread; int to_proc; int to_thread; int to_node; int target_handle; int data_size; int offsets_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,int,char*,int,int,int,int,int,int,int,int) ; 

__attribute__((used)) static char *print_binder_transaction_log_entry(char *buf, char *end,
					struct binder_transaction_log_entry *e)
{
	buf += snprintf(buf, end - buf,
			"%d: %s from %d:%d to %d:%d node %d handle %d "
			"size %d:%d\n",
			e->debug_id, (e->call_type == 2) ? "reply" :
			((e->call_type == 1) ? "async" : "call "), e->from_proc,
			e->from_thread, e->to_proc, e->to_thread, e->to_node,
			e->target_handle, e->data_size, e->offsets_size);
	return buf;
}