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
struct xdr_buf {int /*<<< orphan*/  len; } ;
struct TYPE_3__ {int /*<<< orphan*/ * cr_group_info; } ;
struct svc_rqst {TYPE_1__ rq_cred; int /*<<< orphan*/ * rq_gssclient; int /*<<< orphan*/ * rq_client; struct xdr_buf rq_res; scalar_t__ rq_auth_data; } ;
struct rpc_gss_wire_cred {scalar_t__ gc_proc; int gc_svc; } ;
struct gss_svc_data {TYPE_2__* rsci; int /*<<< orphan*/ * verf_start; struct rpc_gss_wire_cred clcred; } ;
struct TYPE_4__ {int /*<<< orphan*/  h; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ RPC_GSS_PROC_DATA ; 
#define  RPC_GSS_SVC_INTEGRITY 130 
#define  RPC_GSS_SVC_NONE 129 
#define  RPC_GSS_SVC_PRIVACY 128 
 int /*<<< orphan*/  auth_domain_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cache_put (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_group_info (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rsc_cache ; 
 int svcauth_gss_wrap_resp_integ (struct svc_rqst*) ; 
 int svcauth_gss_wrap_resp_priv (struct svc_rqst*) ; 
 int /*<<< orphan*/  total_buf_len (struct xdr_buf*) ; 

__attribute__((used)) static int
svcauth_gss_release(struct svc_rqst *rqstp)
{
	struct gss_svc_data *gsd = (struct gss_svc_data *)rqstp->rq_auth_data;
	struct rpc_gss_wire_cred *gc = &gsd->clcred;
	struct xdr_buf *resbuf = &rqstp->rq_res;
	int stat = -EINVAL;

	if (gc->gc_proc != RPC_GSS_PROC_DATA)
		goto out;
	/* Release can be called twice, but we only wrap once. */
	if (gsd->verf_start == NULL)
		goto out;
	/* normally not set till svc_send, but we need it here: */
	/* XXX: what for?  Do we mess it up the moment we call svc_putu32
	 * or whatever? */
	resbuf->len = total_buf_len(resbuf);
	switch (gc->gc_svc) {
	case RPC_GSS_SVC_NONE:
		break;
	case RPC_GSS_SVC_INTEGRITY:
		stat = svcauth_gss_wrap_resp_integ(rqstp);
		if (stat)
			goto out_err;
		break;
	case RPC_GSS_SVC_PRIVACY:
		stat = svcauth_gss_wrap_resp_priv(rqstp);
		if (stat)
			goto out_err;
		break;
	/*
	 * For any other gc_svc value, svcauth_gss_accept() already set
	 * the auth_error appropriately; just fall through:
	 */
	}

out:
	stat = 0;
out_err:
	if (rqstp->rq_client)
		auth_domain_put(rqstp->rq_client);
	rqstp->rq_client = NULL;
	if (rqstp->rq_gssclient)
		auth_domain_put(rqstp->rq_gssclient);
	rqstp->rq_gssclient = NULL;
	if (rqstp->rq_cred.cr_group_info)
		put_group_info(rqstp->rq_cred.cr_group_info);
	rqstp->rq_cred.cr_group_info = NULL;
	if (gsd->rsci)
		cache_put(&gsd->rsci->h, &rsc_cache);
	gsd->rsci = NULL;

	return stat;
}