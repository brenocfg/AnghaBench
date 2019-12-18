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
typedef  int uint32_t ;
struct rr_server {int /*<<< orphan*/  cid; int /*<<< orphan*/  pid; } ;
struct msm_rpc_endpoint {unsigned int flags; void* dst_vers; void* dst_prog; int /*<<< orphan*/  dst_cid; int /*<<< orphan*/  dst_pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  D (char*,int,int,int) ; 
 int /*<<< orphan*/  EHOSTUNREACH ; 
 struct msm_rpc_endpoint* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct msm_rpc_endpoint*) ; 
 int RPC_VERSION_MODE_MASK ; 
 void* cpu_to_be32 (int) ; 
 scalar_t__ msm_rpc_get_compatible_server (int,int,int*) ; 
 struct msm_rpc_endpoint* msm_rpc_open () ; 
 struct rr_server* rpcrouter_lookup_server (int,int) ; 

struct msm_rpc_endpoint *msm_rpc_connect(uint32_t prog, uint32_t vers, unsigned flags)
{
	struct msm_rpc_endpoint *ept;
	struct rr_server *server;

#if CONFIG_MSM_AMSS_VERSION >= 6350
	if (!(vers & RPC_VERSION_MODE_MASK)) {
		uint32_t found_vers;
		if (msm_rpc_get_compatible_server(prog, vers, &found_vers) < 0)
			return ERR_PTR(-EHOSTUNREACH);
		if (found_vers != vers) {
			D("RPC using new version %08x:{%08x --> %08x}\n",
			 	prog, vers, found_vers);
			vers = found_vers;
		}
	}
#endif

	server = rpcrouter_lookup_server(prog, vers);
	if (!server)
		return ERR_PTR(-EHOSTUNREACH);

	ept = msm_rpc_open();
	if (IS_ERR(ept))
		return ept;

	ept->flags = flags;
	ept->dst_pid = server->pid;
	ept->dst_cid = server->cid;
	ept->dst_prog = cpu_to_be32(prog);
	ept->dst_vers = cpu_to_be32(vers);

	return ept;
}