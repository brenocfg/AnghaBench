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
struct svc_rqst {int /*<<< orphan*/ * rq_gssclient; struct gss_svc_data* rq_auth_data; } ;
struct rsc {int /*<<< orphan*/  mechctx; } ;
struct rpc_gss_wire_cred {int /*<<< orphan*/  gc_svc; } ;
struct gss_svc_data {struct rpc_gss_wire_cred clcred; struct rsc* rsci; } ;

/* Variables and functions */
 int SVC_CLOSE ; 
 int SVC_DENIED ; 
 int SVC_DROP ; 
 int SVC_OK ; 
 int /*<<< orphan*/ * find_gss_auth_domain (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int svcauth_unix_set_client (struct svc_rqst*) ; 

__attribute__((used)) static int
svcauth_gss_set_client(struct svc_rqst *rqstp)
{
	struct gss_svc_data *svcdata = rqstp->rq_auth_data;
	struct rsc *rsci = svcdata->rsci;
	struct rpc_gss_wire_cred *gc = &svcdata->clcred;
	int stat;

	/*
	 * A gss export can be specified either by:
	 * 	export	*(sec=krb5,rw)
	 * or by
	 * 	export gss/krb5(rw)
	 * The latter is deprecated; but for backwards compatibility reasons
	 * the nfsd code will still fall back on trying it if the former
	 * doesn't work; so we try to make both available to nfsd, below.
	 */
	rqstp->rq_gssclient = find_gss_auth_domain(rsci->mechctx, gc->gc_svc);
	if (rqstp->rq_gssclient == NULL)
		return SVC_DENIED;
	stat = svcauth_unix_set_client(rqstp);
	if (stat == SVC_DROP || stat == SVC_CLOSE)
		return stat;
	return SVC_OK;
}