#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rpc_cred {int dummy; } ;
struct auth_cred {int machine_cred; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;
struct TYPE_5__ {TYPE_1__* au_ops; } ;
struct TYPE_4__ {struct rpc_cred* (* lookup_cred ) (TYPE_2__*,struct auth_cred*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  RPC_MACHINE_CRED_GROUPID ; 
 int /*<<< orphan*/  RPC_MACHINE_CRED_USERID ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 TYPE_2__ generic_auth ; 
 struct rpc_cred* stub1 (TYPE_2__*,struct auth_cred*,int /*<<< orphan*/ ) ; 

struct rpc_cred *rpc_lookup_machine_cred(void)
{
	struct auth_cred acred = {
		.uid = RPC_MACHINE_CRED_USERID,
		.gid = RPC_MACHINE_CRED_GROUPID,
		.machine_cred = 1,
	};

	dprintk("RPC:       looking up machine cred\n");
	return generic_auth.au_ops->lookup_cred(&generic_auth, &acred, 0);
}