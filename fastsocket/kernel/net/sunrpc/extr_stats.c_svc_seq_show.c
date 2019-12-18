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
struct svc_version {unsigned int vs_nproc; struct svc_procedure* vs_proc; } ;
struct svc_stat {scalar_t__ rpcbadclnt; scalar_t__ rpcbadauth; scalar_t__ rpcbadfmt; int /*<<< orphan*/  rpccnt; int /*<<< orphan*/  nettcpconn; int /*<<< orphan*/  nettcpcnt; int /*<<< orphan*/  netudpcnt; int /*<<< orphan*/  netcnt; struct svc_program* program; } ;
struct svc_program {unsigned int pg_nvers; struct svc_version** pg_vers; } ;
struct svc_procedure {int /*<<< orphan*/  pc_count; } ;
struct seq_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,unsigned int,...) ; 
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 

void svc_seq_show(struct seq_file *seq, const struct svc_stat *statp) {
	const struct svc_program *prog = statp->program;
	const struct svc_procedure *proc;
	const struct svc_version *vers;
	unsigned int i, j;

	seq_printf(seq,
		"net %u %u %u %u\n",
			statp->netcnt,
			statp->netudpcnt,
			statp->nettcpcnt,
			statp->nettcpconn);
	seq_printf(seq,
		"rpc %u %u %u %u %u\n",
			statp->rpccnt,
			statp->rpcbadfmt+statp->rpcbadauth+statp->rpcbadclnt,
			statp->rpcbadfmt,
			statp->rpcbadauth,
			statp->rpcbadclnt);

	for (i = 0; i < prog->pg_nvers; i++) {
		if (!(vers = prog->pg_vers[i]) || !(proc = vers->vs_proc))
			continue;
		seq_printf(seq, "proc%d %u", i, vers->vs_nproc);
		for (j = 0; j < vers->vs_nproc; j++, proc++)
			seq_printf(seq, " %u", proc->pc_count);
		seq_putc(seq, '\n');
	}
}