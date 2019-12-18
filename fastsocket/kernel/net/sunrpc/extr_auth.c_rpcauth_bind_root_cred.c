#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rpc_task {TYPE_1__* tk_client; int /*<<< orphan*/  tk_pid; } ;
struct rpc_cred {int dummy; } ;
struct rpc_auth {TYPE_2__* au_ops; } ;
struct auth_cred {int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;
struct TYPE_4__ {struct rpc_cred* (* lookup_cred ) (struct rpc_auth*,struct auth_cred*,int) ;int /*<<< orphan*/  au_name; } ;
struct TYPE_3__ {struct rpc_auth* cl_auth; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rpc_cred* stub1 (struct rpc_auth*,struct auth_cred*,int) ; 

__attribute__((used)) static struct rpc_cred *
rpcauth_bind_root_cred(struct rpc_task *task, int lookupflags)
{
	struct rpc_auth *auth = task->tk_client->cl_auth;
	struct auth_cred acred = {
		.uid = 0,
		.gid = 0,
	};

	dprintk("RPC: %5u looking up %s cred\n",
		task->tk_pid, task->tk_client->cl_auth->au_ops->au_name);
	return auth->au_ops->lookup_cred(auth, &acred, lookupflags);
}