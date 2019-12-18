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
struct trace_iterator {struct trace_entry* ent; } ;
struct trace_entry {int type; } ;
typedef  enum print_line_t { ____Placeholder_print_line_t } print_line_t ;
struct TYPE_2__ {int val; } ;

/* Variables and functions */
#define  TRACE_KMEM_ALLOC 129 
#define  TRACE_KMEM_FREE 128 
 int TRACE_KMEM_OPT_MINIMAL ; 
 int TRACE_TYPE_UNHANDLED ; 
 TYPE_1__ kmem_tracer_flags ; 
 int kmemtrace_print_alloc_compress (struct trace_iterator*) ; 
 int kmemtrace_print_free_compress (struct trace_iterator*) ; 

__attribute__((used)) static enum print_line_t kmemtrace_print_line(struct trace_iterator *iter)
{
	struct trace_entry *entry = iter->ent;

	if (!(kmem_tracer_flags.val & TRACE_KMEM_OPT_MINIMAL))
		return TRACE_TYPE_UNHANDLED;

	switch (entry->type) {
	case TRACE_KMEM_ALLOC:
		return kmemtrace_print_alloc_compress(iter);
	case TRACE_KMEM_FREE:
		return kmemtrace_print_free_compress(iter);
	default:
		return TRACE_TYPE_UNHANDLED;
	}
}