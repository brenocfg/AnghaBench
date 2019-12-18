#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* print_fmt; } ;
struct TYPE_4__ {TYPE_1__ fmt; } ;
struct trace_probe {TYPE_2__ call; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int __set_print_fmt (struct trace_probe*,char*,int) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_print_fmt(struct trace_probe *tp)
{
	int len;
	char *print_fmt;

	/* First: called with 0 length to calculate the needed length */
	len = __set_print_fmt(tp, NULL, 0);
	print_fmt = kmalloc(len + 1, GFP_KERNEL);
	if (!print_fmt)
		return -ENOMEM;

	/* Second: actually write the @print_fmt */
	__set_print_fmt(tp, print_fmt, len + 1);
	tp->call.fmt.print_fmt = print_fmt;

	return 0;
}