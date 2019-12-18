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
struct mmiotrace_rw {int opcode; int value; int /*<<< orphan*/  pc; scalar_t__ phys; int /*<<< orphan*/  map_id; int /*<<< orphan*/  width; } ;
struct trace_mmiotrace_rw {struct mmiotrace_rw rw; } ;
struct trace_iterator {int /*<<< orphan*/  ts; struct trace_seq seq; struct trace_entry* ent; } ;
struct trace_entry {int dummy; } ;
typedef  enum print_line_t { ____Placeholder_print_line_t } print_line_t ;

/* Variables and functions */
#define  MMIO_READ 130 
#define  MMIO_UNKNOWN_OP 129 
#define  MMIO_WRITE 128 
 int TRACE_TYPE_HANDLED ; 
 int TRACE_TYPE_PARTIAL_LINE ; 
 int /*<<< orphan*/  USEC_PER_SEC ; 
 unsigned long do_div (unsigned long long,int /*<<< orphan*/ ) ; 
 unsigned long long ns2usecs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_assign_type (struct trace_mmiotrace_rw*,struct trace_entry*) ; 
 int trace_seq_printf (struct trace_seq*,char*,...) ; 

__attribute__((used)) static enum print_line_t mmio_print_rw(struct trace_iterator *iter)
{
	struct trace_entry *entry = iter->ent;
	struct trace_mmiotrace_rw *field;
	struct mmiotrace_rw *rw;
	struct trace_seq *s	= &iter->seq;
	unsigned long long t	= ns2usecs(iter->ts);
	unsigned long usec_rem	= do_div(t, USEC_PER_SEC);
	unsigned secs		= (unsigned long)t;
	int ret = 1;

	trace_assign_type(field, entry);
	rw = &field->rw;

	switch (rw->opcode) {
	case MMIO_READ:
		ret = trace_seq_printf(s,
			"R %d %u.%06lu %d 0x%llx 0x%lx 0x%lx %d\n",
			rw->width, secs, usec_rem, rw->map_id,
			(unsigned long long)rw->phys,
			rw->value, rw->pc, 0);
		break;
	case MMIO_WRITE:
		ret = trace_seq_printf(s,
			"W %d %u.%06lu %d 0x%llx 0x%lx 0x%lx %d\n",
			rw->width, secs, usec_rem, rw->map_id,
			(unsigned long long)rw->phys,
			rw->value, rw->pc, 0);
		break;
	case MMIO_UNKNOWN_OP:
		ret = trace_seq_printf(s,
			"UNKNOWN %u.%06lu %d 0x%llx %02lx,%02lx,"
			"%02lx 0x%lx %d\n",
			secs, usec_rem, rw->map_id,
			(unsigned long long)rw->phys,
			(rw->value >> 16) & 0xff, (rw->value >> 8) & 0xff,
			(rw->value >> 0) & 0xff, rw->pc, 0);
		break;
	default:
		ret = trace_seq_printf(s, "rw what?\n");
		break;
	}
	if (ret)
		return TRACE_TYPE_HANDLED;
	return TRACE_TYPE_PARTIAL_LINE;
}