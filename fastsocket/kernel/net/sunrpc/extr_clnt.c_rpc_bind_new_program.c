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
typedef  size_t u32 ;
struct rpc_version {int /*<<< orphan*/  number; int /*<<< orphan*/  nrprocs; int /*<<< orphan*/  procs; } ;
struct rpc_program {size_t nrvers; int /*<<< orphan*/  stats; int /*<<< orphan*/  number; int /*<<< orphan*/  name; struct rpc_version** version; } ;
struct rpc_clnt {int /*<<< orphan*/  cl_stats; int /*<<< orphan*/  cl_vers; int /*<<< orphan*/  cl_prog; int /*<<< orphan*/  cl_protname; int /*<<< orphan*/  cl_maxproc; int /*<<< orphan*/  cl_procinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct rpc_clnt* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct rpc_clnt*) ; 
 struct rpc_clnt* rpc_clone_client (struct rpc_clnt*) ; 
 int rpc_ping (struct rpc_clnt*) ; 
 int /*<<< orphan*/  rpc_shutdown_client (struct rpc_clnt*) ; 

struct rpc_clnt *rpc_bind_new_program(struct rpc_clnt *old,
				      struct rpc_program *program,
				      u32 vers)
{
	struct rpc_clnt *clnt;
	struct rpc_version *version;
	int err;

	BUG_ON(vers >= program->nrvers || !program->version[vers]);
	version = program->version[vers];
	clnt = rpc_clone_client(old);
	if (IS_ERR(clnt))
		goto out;
	clnt->cl_procinfo = version->procs;
	clnt->cl_maxproc  = version->nrprocs;
	clnt->cl_protname = program->name;
	clnt->cl_prog     = program->number;
	clnt->cl_vers     = version->number;
	clnt->cl_stats    = program->stats;
	err = rpc_ping(clnt);
	if (err != 0) {
		rpc_shutdown_client(clnt);
		clnt = ERR_PTR(err);
	}
out:
	return clnt;
}