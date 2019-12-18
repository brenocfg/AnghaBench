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
typedef  size_t u32 ;
struct svc_serv {int dummy; } ;
struct svc_rqst {int dummy; } ;
struct rpc_xprt {int dummy; } ;
struct nfs_callback_data {int /*<<< orphan*/  users; struct svc_rqst* task; struct svc_rqst* rqst; struct svc_serv* serv; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct svc_rqst*) ; 
 int /*<<< orphan*/  NFS4_CALLBACK_BUFSIZE ; 
 int PTR_ERR (struct svc_rqst*) ; 
 int /*<<< orphan*/  dprintk (char*,int) ; 
 struct svc_rqst* kthread_run (int (*) (void*),struct svc_rqst*,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs4_callback_program ; 
 int nfs4_callback_svc (void*) ; 
 struct svc_rqst* nfs4_callback_up (struct svc_serv*) ; 
 int /*<<< orphan*/  nfs_callback_bc_serv (size_t,struct rpc_xprt*,struct nfs_callback_data*) ; 
 struct nfs_callback_data* nfs_callback_info ; 
 int /*<<< orphan*/  nfs_callback_mutex ; 
 int nfs_minorversion_callback_svc_setup (size_t,struct svc_serv*,struct rpc_xprt*,struct svc_rqst**,int (*) (void*)) ; 
 int /*<<< orphan*/  sprintf (char*,char*,size_t) ; 
 struct svc_serv* svc_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svc_destroy (struct svc_serv*) ; 
 int /*<<< orphan*/  svc_exit_thread (struct svc_rqst*) ; 
 int /*<<< orphan*/  svc_sock_update_bufs (struct svc_serv*) ; 

int nfs_callback_up(u32 minorversion, struct rpc_xprt *xprt)
{
	struct svc_serv *serv = NULL;
	struct svc_rqst *rqstp;
	int (*callback_svc)(void *vrqstp);
	struct nfs_callback_data *cb_info = &nfs_callback_info[minorversion];
	char svc_name[12];
	int ret = 0;
	int minorversion_setup;

	mutex_lock(&nfs_callback_mutex);
	if (cb_info->users++ || cb_info->task != NULL) {
		nfs_callback_bc_serv(minorversion, xprt, cb_info);
		goto out;
	}
	serv = svc_create(&nfs4_callback_program, NFS4_CALLBACK_BUFSIZE, NULL);
	if (!serv) {
		ret = -ENOMEM;
		goto out_err;
	}

	minorversion_setup =  nfs_minorversion_callback_svc_setup(minorversion,
					serv, xprt, &rqstp, &callback_svc);
	if (!minorversion_setup) {
		/* v4.0 callback setup */
		rqstp = nfs4_callback_up(serv);
		callback_svc = nfs4_callback_svc;
	}

	if (IS_ERR(rqstp)) {
		ret = PTR_ERR(rqstp);
		goto out_err;
	}

	svc_sock_update_bufs(serv);

	sprintf(svc_name, "nfsv4.%u-svc", minorversion);
	cb_info->serv = serv;
	cb_info->rqst = rqstp;
	cb_info->task = kthread_run(callback_svc, cb_info->rqst, svc_name);
	if (IS_ERR(cb_info->task)) {
		ret = PTR_ERR(cb_info->task);
		svc_exit_thread(cb_info->rqst);
		cb_info->rqst = NULL;
		cb_info->task = NULL;
		goto out_err;
	}
out:
	/*
	 * svc_create creates the svc_serv with sv_nrthreads == 1, and then
	 * svc_prepare_thread increments that. So we need to call svc_destroy
	 * on both success and failure so that the refcount is 1 when the
	 * thread exits.
	 */
	if (serv)
		svc_destroy(serv);
	mutex_unlock(&nfs_callback_mutex);
	return ret;
out_err:
	dprintk("NFS: Couldn't create callback socket or server thread; "
		"err = %d\n", ret);
	cb_info->users--;
	goto out;
}