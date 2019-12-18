#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  dentry; } ;
struct rpc_clnt {scalar_t__ cl_server; scalar_t__ cl_inline_name; int /*<<< orphan*/  cl_xprt; int /*<<< orphan*/ * cl_metrics; struct rpc_clnt* cl_principal; struct rpc_clnt* cl_parent; TYPE_1__ cl_path; int /*<<< orphan*/  cl_protname; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct rpc_clnt*) ; 
 int /*<<< orphan*/  rpc_free_iostats (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpc_put_mount () ; 
 int /*<<< orphan*/  rpc_release_client (struct rpc_clnt*) ; 
 int /*<<< orphan*/  rpc_remove_client_dir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_unregister_client (struct rpc_clnt*) ; 
 int /*<<< orphan*/  rpciod_down () ; 
 int /*<<< orphan*/  xprt_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
rpc_free_client(struct rpc_clnt *clnt)
{
	dprintk("RPC:       destroying %s client for %s\n",
			clnt->cl_protname, clnt->cl_server);
	if (!IS_ERR(clnt->cl_path.dentry)) {
		rpc_remove_client_dir(clnt->cl_path.dentry);
		rpc_put_mount();
	}
	if (clnt->cl_parent != clnt) {
		rpc_release_client(clnt->cl_parent);
		goto out_free;
	}
	if (clnt->cl_server != clnt->cl_inline_name)
		kfree(clnt->cl_server);
out_free:
	rpc_unregister_client(clnt);
	rpc_free_iostats(clnt->cl_metrics);
	kfree(clnt->cl_principal);
	clnt->cl_metrics = NULL;
	xprt_put(clnt->cl_xprt);
	rpciod_down();
	kfree(clnt);
}