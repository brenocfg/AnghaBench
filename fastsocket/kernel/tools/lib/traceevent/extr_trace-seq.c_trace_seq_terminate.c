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
struct trace_seq {size_t len; scalar_t__* buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE_SEQ_CHECK (struct trace_seq*) ; 

void trace_seq_terminate(struct trace_seq *s)
{
	TRACE_SEQ_CHECK(s);

	/* There's always one character left on the buffer */
	s->buffer[s->len] = 0;
}