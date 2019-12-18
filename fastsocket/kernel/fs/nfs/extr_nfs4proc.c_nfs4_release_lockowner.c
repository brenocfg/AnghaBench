#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct rpc_message {TYPE_4__* rpc_argp; int /*<<< orphan*/ * rpc_proc; } ;
struct nfs_server {int /*<<< orphan*/  client; int /*<<< orphan*/  s_dev; TYPE_1__* nfs_client; } ;
struct TYPE_7__ {int /*<<< orphan*/  s_dev; int /*<<< orphan*/  id; int /*<<< orphan*/  clientid; } ;
struct TYPE_8__ {TYPE_3__ lock_owner; } ;
struct nfs_release_lockowner_data {TYPE_4__ args; struct nfs_server* server; struct nfs4_lock_state* lsp; } ;
struct TYPE_6__ {int /*<<< orphan*/  id; } ;
struct nfs4_lock_state {TYPE_2__ ls_id; } ;
struct TYPE_5__ {scalar_t__ cl_minorversion; int /*<<< orphan*/  cl_clientid; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 size_t NFSPROC4_CLNT_RELEASE_LOCKOWNER ; 
 struct nfs_release_lockowner_data* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nfs4_procedures ; 
 int /*<<< orphan*/  nfs4_release_lockowner_ops ; 
 int /*<<< orphan*/  rpc_call_async (int /*<<< orphan*/ ,struct rpc_message*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct nfs_release_lockowner_data*) ; 

__attribute__((used)) static int nfs4_release_lockowner(struct nfs_server *server, struct nfs4_lock_state *lsp)
{
	struct nfs_release_lockowner_data *data;
	struct rpc_message msg = {
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_RELEASE_LOCKOWNER],
	};

	if (server->nfs_client->cl_minorversion != 0)
		return -EINVAL;
	data = kmalloc(sizeof(*data), GFP_NOFS);
	if (!data)
		return -ENOMEM;
	data->lsp = lsp;
	data->server = server;
	data->args.lock_owner.clientid = server->nfs_client->cl_clientid;
	data->args.lock_owner.id = lsp->ls_id.id;
	data->args.lock_owner.s_dev = server->s_dev;
	msg.rpc_argp = &data->args;
	rpc_call_async(server->client, &msg, 0, &nfs4_release_lockowner_ops, data);
	return 0;
}