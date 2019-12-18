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
typedef  int /*<<< orphan*/  va_list ;

/* Variables and functions */
 int TRACE_ITER_PRINTK ; 
 int trace_flags ; 
 int trace_vbprintk (unsigned long,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

int __ftrace_vbprintk(unsigned long ip, const char *fmt, va_list ap)
 {
	if (unlikely(!fmt))
		return 0;

	if (!(trace_flags & TRACE_ITER_PRINTK))
		return 0;

	return trace_vbprintk(ip, fmt, ap);
}