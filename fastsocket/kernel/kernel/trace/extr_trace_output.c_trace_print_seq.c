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
struct trace_seq {int len; int /*<<< orphan*/  buffer; } ;
struct seq_file {int dummy; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/  seq_write (struct seq_file*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  trace_seq_init (struct trace_seq*) ; 

void trace_print_seq(struct seq_file *m, struct trace_seq *s)
{
	int len = s->len >= PAGE_SIZE ? PAGE_SIZE - 1 : s->len;

	seq_write(m, s->buffer, len);

	trace_seq_init(s);
}