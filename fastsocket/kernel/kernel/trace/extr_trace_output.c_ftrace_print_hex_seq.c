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

/* Variables and functions */
 int /*<<< orphan*/  trace_seq_printf (struct trace_seq*,char*,char*,unsigned char const) ; 
 int /*<<< orphan*/  trace_seq_putc (struct trace_seq*,int /*<<< orphan*/ ) ; 

const char *
ftrace_print_hex_seq(struct trace_seq *p, const unsigned char *buf, int buf_len)
{
	int i;
	const char *ret = p->buffer + p->len;

	for (i = 0; i < buf_len; i++)
		trace_seq_printf(p, "%s%2.2x", i == 0 ? "" : " ", buf[i]);

	trace_seq_putc(p, 0);

	return ret;
}