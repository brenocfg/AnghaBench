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
struct super_block {int dummy; } ;
struct rpc_clnt {int dummy; } ;
struct nfs_server {struct rpc_clnt* client; struct rpc_clnt* client_acl; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct rpc_clnt*) ; 
 struct nfs_server* NFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  rpc_killall_tasks (struct rpc_clnt*) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static void nfs_umount_begin(struct super_block *sb)
{
	struct nfs_server *server;
	struct rpc_clnt *rpc;

	lock_kernel();

	server = NFS_SB(sb);
	/* -EIO all pending I/O */
	rpc = server->client_acl;
	if (!IS_ERR(rpc))
		rpc_killall_tasks(rpc);
	rpc = server->client;
	if (!IS_ERR(rpc))
		rpc_killall_tasks(rpc);

	unlock_kernel();
}