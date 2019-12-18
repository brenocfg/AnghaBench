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
struct msm_rpc_endpoint {int dummy; } ;
typedef  int /*<<< orphan*/  rep ;

/* Variables and functions */
 int RPCMSG_REPLYSTAT_ACCEPTED ; 
 int RPC_ACCEPTSTAT_SUCCESS ; 
 int cpu_to_be32 (int) ; 
 int /*<<< orphan*/  msm_rpc_write (struct msm_rpc_endpoint*,int*,int) ; 

__attribute__((used)) static void rpc_ack(struct msm_rpc_endpoint *ept, uint32_t xid)
{
	uint32_t rep[6];

	rep[0] = cpu_to_be32(xid);
	rep[1] = cpu_to_be32(1);
	rep[2] = cpu_to_be32(RPCMSG_REPLYSTAT_ACCEPTED);
	rep[3] = cpu_to_be32(RPC_ACCEPTSTAT_SUCCESS);
	rep[4] = 0;
	rep[5] = 0;

	msm_rpc_write(ept, rep, sizeof(rep));
}