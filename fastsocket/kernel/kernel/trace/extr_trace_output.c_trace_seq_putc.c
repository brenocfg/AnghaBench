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
struct trace_seq {int len; unsigned char* buffer; } ;

/* Variables and functions */
 int PAGE_SIZE ; 

int trace_seq_putc(struct trace_seq *s, unsigned char c)
{
	if (s->len >= (PAGE_SIZE - 1))
		return 0;

	s->buffer[s->len++] = c;

	return 1;
}