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
struct trace_seq {int buffer_size; int len; scalar_t__ buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE_SEQ_CHECK (struct trace_seq*) ; 
 int /*<<< orphan*/  expand_buffer (struct trace_seq*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char const*,int) ; 
 int strlen (char const*) ; 

int trace_seq_puts(struct trace_seq *s, const char *str)
{
	int len;

	TRACE_SEQ_CHECK(s);

	len = strlen(str);

	while (len > ((s->buffer_size - 1) - s->len))
		expand_buffer(s);

	memcpy(s->buffer + s->len, str, len);
	s->len += len;

	return len;
}