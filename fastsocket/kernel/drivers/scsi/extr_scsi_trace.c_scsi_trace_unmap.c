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
struct trace_seq {char* buffer; int len; } ;

/* Variables and functions */
 int /*<<< orphan*/  trace_seq_printf (struct trace_seq*,char*,unsigned int) ; 
 int /*<<< orphan*/  trace_seq_putc (struct trace_seq*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *
scsi_trace_unmap(struct trace_seq *p, unsigned char *cdb, int len)
{
	const char *ret = p->buffer + p->len;
	unsigned int regions = cdb[7] << 8 | cdb[8];

	trace_seq_printf(p, "regions=%u", (regions - 8) / 16);
	trace_seq_putc(p, 0);

	return ret;
}