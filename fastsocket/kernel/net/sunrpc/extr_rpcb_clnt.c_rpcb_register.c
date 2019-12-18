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
typedef  int /*<<< orphan*/  u32 ;
struct rpcbind_args {int r_prot; unsigned short r_port; int /*<<< orphan*/  r_vers; int /*<<< orphan*/  r_prog; } ;
struct rpc_message {int /*<<< orphan*/ * rpc_proc; struct rpcbind_args* rpc_argp; } ;

/* Variables and functions */
 size_t RPCBPROC_SET ; 
 size_t RPCBPROC_UNSET ; 
 int /*<<< orphan*/  dprintk (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned short) ; 
 int /*<<< orphan*/  rpcb_local_clnt ; 
 int /*<<< orphan*/ * rpcb_procedures2 ; 
 int rpcb_register_call (int /*<<< orphan*/ ,struct rpc_message*) ; 

int rpcb_register(u32 prog, u32 vers, int prot, unsigned short port)
{
	struct rpcbind_args map = {
		.r_prog		= prog,
		.r_vers		= vers,
		.r_prot		= prot,
		.r_port		= port,
	};
	struct rpc_message msg = {
		.rpc_argp	= &map,
	};

	dprintk("RPC:       %sregistering (%u, %u, %d, %u) with local "
			"rpcbind\n", (port ? "" : "un"),
			prog, vers, prot, port);

	msg.rpc_proc = &rpcb_procedures2[RPCBPROC_UNSET];
	if (port)
		msg.rpc_proc = &rpcb_procedures2[RPCBPROC_SET];

	return rpcb_register_call(rpcb_local_clnt, &msg);
}