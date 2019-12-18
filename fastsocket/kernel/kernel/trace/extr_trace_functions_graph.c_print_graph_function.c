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
struct trace_iterator {int dummy; } ;
typedef  enum print_line_t { ____Placeholder_print_line_t } print_line_t ;
struct TYPE_2__ {int /*<<< orphan*/  val; } ;

/* Variables and functions */
 int __print_graph_function_flags (struct trace_iterator*,int /*<<< orphan*/ ) ; 
 TYPE_1__ tracer_flags ; 

__attribute__((used)) static enum print_line_t
print_graph_function(struct trace_iterator *iter)
{
	return __print_graph_function_flags(iter, tracer_flags.val);
}