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
struct seq_file {int dummy; } ;
struct TYPE_2__ {int val; } ;

/* Variables and functions */
 int TRACE_KMEM_OPT_MINIMAL ; 
 TYPE_1__ kmem_tracer_flags ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*) ; 

__attribute__((used)) static void kmemtrace_headers(struct seq_file *s)
{
	/* Don't need headers for the original kmemtrace output */
	if (!(kmem_tracer_flags.val & TRACE_KMEM_OPT_MINIMAL))
		return;

	seq_printf(s, "#\n");
	seq_printf(s, "# ALLOC  TYPE  REQ   GIVEN  FLAGS     "
			"      POINTER         NODE    CALLER\n");
	seq_printf(s, "# FREE   |      |     |       |       "
			"       |   |            |        |\n");
	seq_printf(s, "# |\n\n");
}