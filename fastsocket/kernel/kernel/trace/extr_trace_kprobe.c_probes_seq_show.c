#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ offset; int /*<<< orphan*/  addr; } ;
struct TYPE_7__ {TYPE_2__ kp; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; int /*<<< orphan*/  system; } ;
struct trace_probe {int nr_args; TYPE_4__* args; TYPE_3__ rp; int /*<<< orphan*/  symbol; TYPE_1__ call; } ;
struct seq_file {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  comm; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 
 scalar_t__ trace_probe_is_return (struct trace_probe*) ; 
 int /*<<< orphan*/  trace_probe_symbol (struct trace_probe*) ; 

__attribute__((used)) static int probes_seq_show(struct seq_file *m, void *v)
{
	struct trace_probe *tp = v;
	int i;

	seq_printf(m, "%c", trace_probe_is_return(tp) ? 'r' : 'p');
	seq_printf(m, ":%s/%s", tp->call.system, tp->call.name);

	if (!tp->symbol)
		seq_printf(m, " 0x%p", tp->rp.kp.addr);
	else if (tp->rp.kp.offset)
		seq_printf(m, " %s+%u", trace_probe_symbol(tp),
			   tp->rp.kp.offset);
	else
		seq_printf(m, " %s", trace_probe_symbol(tp));

	for (i = 0; i < tp->nr_args; i++)
		seq_printf(m, " %s=%s", tp->args[i].name, tp->args[i].comm);
	seq_printf(m, "\n");

	return 0;
}