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
struct rpcbind_args {char* r_addr; int /*<<< orphan*/  r_netid; int /*<<< orphan*/  r_vers; int /*<<< orphan*/  r_prog; } ;
struct rpc_message {int /*<<< orphan*/ * rpc_proc; struct rpcbind_args* rpc_argp; } ;

/* Variables and functions */
 size_t RPCBPROC_UNSET ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpcb_local_clnt4 ; 
 int /*<<< orphan*/ * rpcb_procedures4 ; 
 int rpcb_register_call (int /*<<< orphan*/ ,struct rpc_message*) ; 

__attribute__((used)) static int rpcb_unregister_all_protofamilies(struct rpc_message *msg)
{
	struct rpcbind_args *map = msg->rpc_argp;

	dprintk("RPC:       unregistering [%u, %u, '%s'] with "
		"local rpcbind\n",
			map->r_prog, map->r_vers, map->r_netid);

	map->r_addr = "";
	msg->rpc_proc = &rpcb_procedures4[RPCBPROC_UNSET];

	return rpcb_register_call(rpcb_local_clnt4, msg);
}