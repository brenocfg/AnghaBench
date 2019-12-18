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
struct trace_seq {int len; int buffer_size; unsigned char* buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE_SEQ_CHECK (struct trace_seq*) ; 
 int /*<<< orphan*/  expand_buffer (struct trace_seq*) ; 

int trace_seq_putc(struct trace_seq *s, unsigned char c)
{
	TRACE_SEQ_CHECK(s);

	while (s->len >= (s->buffer_size - 1))
		expand_buffer(s);

	s->buffer[s->len++] = c;

	return 1;
}