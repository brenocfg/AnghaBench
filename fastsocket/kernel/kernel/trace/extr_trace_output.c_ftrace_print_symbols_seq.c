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
struct trace_seq {char* buffer; int len; } ;
struct trace_print_flags {unsigned long mask; scalar_t__ name; } ;

/* Variables and functions */
 int /*<<< orphan*/  trace_seq_printf (struct trace_seq*,char*,unsigned long) ; 
 int /*<<< orphan*/  trace_seq_putc (struct trace_seq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_seq_puts (struct trace_seq*,scalar_t__) ; 

const char *
ftrace_print_symbols_seq(struct trace_seq *p, unsigned long val,
			 const struct trace_print_flags *symbol_array)
{
	int i;
	const char *ret = p->buffer + p->len;

	for (i = 0;  symbol_array[i].name; i++) {

		if (val != symbol_array[i].mask)
			continue;

		trace_seq_puts(p, symbol_array[i].name);
		break;
	}

	if (ret == (const char *)(p->buffer + p->len))
		trace_seq_printf(p, "0x%lx", val);
		
	trace_seq_putc(p, 0);

	return ret;
}