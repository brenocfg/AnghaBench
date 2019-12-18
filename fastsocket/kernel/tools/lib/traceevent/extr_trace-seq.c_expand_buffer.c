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
struct trace_seq {int /*<<< orphan*/  buffer; int /*<<< orphan*/  buffer_size; } ;

/* Variables and functions */
 scalar_t__ TRACE_SEQ_BUF_SIZE ; 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  realloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void expand_buffer(struct trace_seq *s)
{
	s->buffer_size += TRACE_SEQ_BUF_SIZE;
	s->buffer = realloc(s->buffer, s->buffer_size);
	if (!s->buffer)
		die("Can't allocate trace_seq buffer memory");
}