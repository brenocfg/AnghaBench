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
struct rpc_clnt {int dummy; } ;
struct qstr {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int S_IRUGO ; 
 int S_IXUGO ; 
 int /*<<< orphan*/  rpc_clntdir_populate ; 
 struct dentry* rpc_mkdir_populate (struct dentry*,struct qstr*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct rpc_clnt*) ; 

struct dentry *rpc_create_client_dir(struct dentry *dentry,
				   struct qstr *name,
				   struct rpc_clnt *rpc_client)
{
	return rpc_mkdir_populate(dentry, name, S_IRUGO | S_IXUGO, NULL,
			rpc_clntdir_populate, rpc_client);
}