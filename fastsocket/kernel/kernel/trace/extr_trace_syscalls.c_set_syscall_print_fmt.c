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
struct syscall_metadata {struct ftrace_event_call* enter_event; } ;
struct TYPE_2__ {char* print_fmt; } ;
struct ftrace_event_call {TYPE_1__ fmt; struct syscall_metadata* data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int __set_enter_print_fmt (struct syscall_metadata*,char*,int) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 

int set_syscall_print_fmt(struct ftrace_event_call *call)
{
	char *print_fmt;
	int len;
	struct syscall_metadata *entry = call->data;

	if (entry->enter_event != call) {
		call->fmt.print_fmt = "\"0x%lx\", REC->ret";
		return 0;
	}

	/* First: called with 0 length to calculate the needed length */
	len = __set_enter_print_fmt(entry, NULL, 0);

	print_fmt = kmalloc(len + 1, GFP_KERNEL);
	if (!print_fmt)
		return -ENOMEM;

	/* Second: actually write the @print_fmt */
	__set_enter_print_fmt(entry, print_fmt, len + 1);
	call->fmt.print_fmt = print_fmt;

	return 0;
}