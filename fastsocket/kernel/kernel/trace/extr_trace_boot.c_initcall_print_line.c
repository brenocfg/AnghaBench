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
struct trace_iterator {struct trace_entry* ent; } ;
struct trace_entry {int type; } ;
typedef  enum print_line_t { ____Placeholder_print_line_t } print_line_t ;

/* Variables and functions */
#define  TRACE_BOOT_CALL 129 
#define  TRACE_BOOT_RET 128 
 int TRACE_TYPE_UNHANDLED ; 
 int initcall_call_print_line (struct trace_iterator*) ; 
 int initcall_ret_print_line (struct trace_iterator*) ; 

__attribute__((used)) static enum print_line_t initcall_print_line(struct trace_iterator *iter)
{
	struct trace_entry *entry = iter->ent;

	switch (entry->type) {
	case TRACE_BOOT_CALL:
		return initcall_call_print_line(iter);
	case TRACE_BOOT_RET:
		return initcall_ret_print_line(iter);
	default:
		return TRACE_TYPE_UNHANDLED;
	}
}