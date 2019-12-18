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
struct trace_seq {char* len; int /*<<< orphan*/  buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE_SEQ_CHECK (struct trace_seq*) ; 
 int printf (char*,char*,int /*<<< orphan*/ ) ; 

int trace_seq_do_printf(struct trace_seq *s)
{
	TRACE_SEQ_CHECK(s);
	return printf("%.*s", s->len, s->buffer);
}