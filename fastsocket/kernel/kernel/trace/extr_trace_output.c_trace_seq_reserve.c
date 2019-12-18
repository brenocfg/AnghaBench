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
struct trace_seq {int len; void* buffer; } ;

/* Variables and functions */
 int PAGE_SIZE ; 

void *trace_seq_reserve(struct trace_seq *s, size_t len)
{
	void *ret;

	if (len > ((PAGE_SIZE - 1) - s->len))
		return NULL;

	ret = s->buffer + s->len;
	s->len += len;

	return ret;
}