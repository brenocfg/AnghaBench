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
struct trace_seq {int buffer_size; int len; scalar_t__ buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE_SEQ_CHECK (struct trace_seq*) ; 
 int /*<<< orphan*/  expand_buffer (struct trace_seq*) ; 
 int vsnprintf (scalar_t__,int,char const*,int /*<<< orphan*/ ) ; 

int
trace_seq_vprintf(struct trace_seq *s, const char *fmt, va_list args)
{
	int len;
	int ret;

	TRACE_SEQ_CHECK(s);

 try_again:
	len = (s->buffer_size - 1) - s->len;

	ret = vsnprintf(s->buffer + s->len, len, fmt, args);

	if (ret >= len) {
		expand_buffer(s);
		goto try_again;
	}

	s->len += ret;

	return len;
}