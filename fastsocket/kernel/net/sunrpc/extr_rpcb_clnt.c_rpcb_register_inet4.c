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
struct sockaddr_in {int /*<<< orphan*/  sin_port; } ;
struct sockaddr {int dummy; } ;
struct rpcbind_args {int /*<<< orphan*/  r_addr; int /*<<< orphan*/  r_netid; int /*<<< orphan*/  r_vers; int /*<<< orphan*/  r_prog; } ;
struct rpc_message {int /*<<< orphan*/ * rpc_proc; struct rpcbind_args* rpc_argp; } ;

/* Variables and functions */
 size_t RPCBPROC_SET ; 
 size_t RPCBPROC_UNSET ; 
 int /*<<< orphan*/  dprintk (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 unsigned short ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_sockaddr2uaddr (struct sockaddr const*) ; 
 int /*<<< orphan*/  rpcb_local_clnt4 ; 
 int /*<<< orphan*/ * rpcb_procedures4 ; 
 int rpcb_register_call (int /*<<< orphan*/ ,struct rpc_message*) ; 

__attribute__((used)) static int rpcb_register_inet4(const struct sockaddr *sap,
			       struct rpc_message *msg)
{
	const struct sockaddr_in *sin = (const struct sockaddr_in *)sap;
	struct rpcbind_args *map = msg->rpc_argp;
	unsigned short port = ntohs(sin->sin_port);
	int result;

	map->r_addr = rpc_sockaddr2uaddr(sap);

	dprintk("RPC:       %sregistering [%u, %u, %s, '%s'] with "
		"local rpcbind\n", (port ? "" : "un"),
			map->r_prog, map->r_vers,
			map->r_addr, map->r_netid);

	msg->rpc_proc = &rpcb_procedures4[RPCBPROC_UNSET];
	if (port)
		msg->rpc_proc = &rpcb_procedures4[RPCBPROC_SET];

	result = rpcb_register_call(rpcb_local_clnt4, msg);
	kfree(map->r_addr);
	return result;
}