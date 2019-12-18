#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct seq_file {struct rpc_stat* private; } ;
struct rpc_version {unsigned int nrprocs; TYPE_1__* procs; int /*<<< orphan*/  number; } ;
struct rpc_stat {int /*<<< orphan*/  rpcauthrefresh; int /*<<< orphan*/  rpcretrans; int /*<<< orphan*/  rpccnt; int /*<<< orphan*/  nettcpconn; int /*<<< orphan*/  nettcpcnt; int /*<<< orphan*/  netudpcnt; int /*<<< orphan*/  netcnt; struct rpc_program* program; } ;
struct rpc_program {unsigned int nrvers; struct rpc_version** version; } ;
struct TYPE_2__ {int /*<<< orphan*/  p_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 

__attribute__((used)) static int rpc_proc_show(struct seq_file *seq, void *v) {
	const struct rpc_stat	*statp = seq->private;
	const struct rpc_program *prog = statp->program;
	unsigned int i, j;

	seq_printf(seq,
		"net %u %u %u %u\n",
			statp->netcnt,
			statp->netudpcnt,
			statp->nettcpcnt,
			statp->nettcpconn);
	seq_printf(seq,
		"rpc %u %u %u\n",
			statp->rpccnt,
			statp->rpcretrans,
			statp->rpcauthrefresh);

	for (i = 0; i < prog->nrvers; i++) {
		const struct rpc_version *vers = prog->version[i];
		if (!vers)
			continue;
		seq_printf(seq, "proc%u %u",
					vers->number, vers->nrprocs);
		for (j = 0; j < vers->nrprocs; j++)
			seq_printf(seq, " %u",
					vers->procs[j].p_count);
		seq_putc(seq, '\n');
	}
	return 0;
}