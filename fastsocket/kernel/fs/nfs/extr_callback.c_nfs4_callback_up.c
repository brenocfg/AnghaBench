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
struct svc_serv {int /*<<< orphan*/ * sv_pools; } ;
struct svc_rqst {int dummy; } ;

/* Variables and functions */
 int EAFNOSUPPORT ; 
 int ENOMEM ; 
 struct svc_rqst* ERR_PTR (int) ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  PF_INET6 ; 
 int /*<<< orphan*/  SVC_SOCK_ANONYMOUS ; 
 int /*<<< orphan*/  dprintk (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  nfs_callback_set_tcpport ; 
 int nfs_callback_tcpport ; 
 int nfs_callback_tcpport6 ; 
 int svc_create_xprt (struct svc_serv*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct svc_rqst* svc_prepare_thread (struct svc_serv*,int /*<<< orphan*/ *) ; 

struct svc_rqst *
nfs4_callback_up(struct svc_serv *serv)
{
	int ret;

	ret = svc_create_xprt(serv, "tcp", &init_net, PF_INET,
				nfs_callback_set_tcpport, SVC_SOCK_ANONYMOUS);
	if (ret <= 0)
		goto out_err;
	nfs_callback_tcpport = ret;
	dprintk("NFS: Callback listener port = %u (af %u)\n",
			nfs_callback_tcpport, PF_INET);

	ret = svc_create_xprt(serv, "tcp", &init_net, PF_INET6,
				nfs_callback_set_tcpport, SVC_SOCK_ANONYMOUS);
	if (ret > 0) {
		nfs_callback_tcpport6 = ret;
		dprintk("NFS: Callback listener port = %u (af %u)\n",
				nfs_callback_tcpport6, PF_INET6);
	} else if (ret == -EAFNOSUPPORT)
		ret = 0;
	else
		goto out_err;

	return svc_prepare_thread(serv, &serv->sv_pools[0]);

out_err:
	if (ret == 0)
		ret = -ENOMEM;
	return ERR_PTR(ret);
}