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
struct trace_seq {int dummy; } ;
struct trace_iterator {int /*<<< orphan*/  ts; struct trace_seq seq; struct trace_entry* ent; } ;
struct trace_entry {int dummy; } ;
struct print_entry {char* buf; } ;
typedef  enum print_line_t { ____Placeholder_print_line_t } print_line_t ;

/* Variables and functions */
 int TRACE_TYPE_HANDLED ; 
 int TRACE_TYPE_PARTIAL_LINE ; 
 int /*<<< orphan*/  USEC_PER_SEC ; 
 unsigned long do_div (unsigned long long,int /*<<< orphan*/ ) ; 
 unsigned long long ns2usecs (int /*<<< orphan*/ ) ; 
 int trace_seq_printf (struct trace_seq*,char*,unsigned int,unsigned long,char const*) ; 

__attribute__((used)) static enum print_line_t mmio_print_mark(struct trace_iterator *iter)
{
	struct trace_entry *entry = iter->ent;
	struct print_entry *print = (struct print_entry *)entry;
	const char *msg		= print->buf;
	struct trace_seq *s	= &iter->seq;
	unsigned long long t	= ns2usecs(iter->ts);
	unsigned long usec_rem	= do_div(t, USEC_PER_SEC);
	unsigned secs		= (unsigned long)t;
	int ret;

	/* The trailing newline must be in the message. */
	ret = trace_seq_printf(s, "MARK %u.%06lu %s", secs, usec_rem, msg);
	if (!ret)
		return TRACE_TYPE_PARTIAL_LINE;

	return TRACE_TYPE_HANDLED;
}