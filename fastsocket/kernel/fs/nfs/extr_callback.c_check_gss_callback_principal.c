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
struct svc_rqst {TYPE_1__* rq_authop; } ;
struct rpc_clnt {int /*<<< orphan*/  cl_server; } ;
struct nfs_client {scalar_t__ cl_minorversion; struct rpc_clnt* cl_rpcclient; } ;
struct TYPE_2__ {scalar_t__ flavour; } ;

/* Variables and functions */
 scalar_t__ RPC_AUTH_GSS ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 char* svc_gss_principal (struct svc_rqst*) ; 

int
check_gss_callback_principal(struct nfs_client *clp, struct svc_rqst *rqstp)
{
	struct rpc_clnt *r = clp->cl_rpcclient;
	char *p = svc_gss_principal(rqstp);

	if (rqstp->rq_authop->flavour != RPC_AUTH_GSS)
		return 1;

	/* No RPC_AUTH_GSS on NFSv4.1 back channel yet */
	if (clp->cl_minorversion != 0)
		return 0;
	/*
	 * It might just be a normal user principal, in which case
	 * userspace won't bother to tell us the name at all.
	 */
	if (p == NULL)
		return 0;

	/* Expect a GSS_C_NT_HOSTBASED_NAME like "nfs@serverhostname" */

	if (memcmp(p, "nfs@", 4) != 0)
		return 0;
	p += 4;
	if (strcmp(p, r->cl_server) != 0)
		return 0;
	return 1;
}