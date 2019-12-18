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
struct rpc_message {int dummy; } ;
struct rpc_clnt {int dummy; } ;
struct nfs_server {TYPE_2__* nfs_client; } ;
struct nfs4_sequence_res {int dummy; } ;
struct nfs4_sequence_args {int dummy; } ;
struct TYPE_4__ {TYPE_1__* cl_mvops; } ;
struct TYPE_3__ {int (* call_sync ) (struct rpc_clnt*,struct nfs_server*,struct rpc_message*,struct nfs4_sequence_args*,struct nfs4_sequence_res*,int) ;} ;

/* Variables and functions */
 int stub1 (struct rpc_clnt*,struct nfs_server*,struct rpc_message*,struct nfs4_sequence_args*,struct nfs4_sequence_res*,int) ; 

__attribute__((used)) static inline
int nfs4_call_sync(struct rpc_clnt *clnt,
		   struct nfs_server *server,
		   struct rpc_message *msg,
		   struct nfs4_sequence_args *args,
		   struct nfs4_sequence_res *res,
		   int cache_reply)
{
	return server->nfs_client->cl_mvops->call_sync(clnt, server, msg,
						args, res, cache_reply);
}