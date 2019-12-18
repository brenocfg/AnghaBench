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
struct trace_array_cpu {int dummy; } ;
struct trace_array {int dummy; } ;
struct pt_regs {int /*<<< orphan*/  ip; } ;
struct backtrace_info {int pos; struct trace_array_cpu* data; struct trace_array* tr; } ;

/* Variables and functions */
 int /*<<< orphan*/  __trace_special (struct trace_array*,struct trace_array_cpu*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  backtrace_ops ; 
 int /*<<< orphan*/  dump_trace (int /*<<< orphan*/ *,struct pt_regs*,void*,int /*<<< orphan*/ *,struct backtrace_info*) ; 

__attribute__((used)) static int
trace_kernel(struct pt_regs *regs, struct trace_array *tr,
	     struct trace_array_cpu *data)
{
	struct backtrace_info info;
	char *stack;

	info.tr = tr;
	info.data = data;
	info.pos = 1;

	__trace_special(info.tr, info.data, 1, regs->ip, 0);
	stack = ((char *)regs + sizeof(struct pt_regs));
	dump_trace(NULL, regs, (void *)stack, &backtrace_ops, &info);

	return info.pos;
}