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
typedef  int /*<<< orphan*/  u32 ;
struct svc_rqst {int /*<<< orphan*/  rq_chandle; int /*<<< orphan*/ * rq_gssclient; int /*<<< orphan*/ * rq_client; } ;
struct svc_export {scalar_t__ ex_nflavors; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 struct svc_export* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct svc_export*) ; 
 int /*<<< orphan*/  PTR_ERR (struct svc_export*) ; 
 struct svc_export* exp_find (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exp_put (struct svc_export*) ; 

struct svc_export *
rqst_exp_find(struct svc_rqst *rqstp, int fsid_type, u32 *fsidv)
{
	struct svc_export *gssexp, *exp = ERR_PTR(-ENOENT);

	if (rqstp->rq_client == NULL)
		goto gss;

	/* First try the auth_unix client: */
	exp = exp_find(rqstp->rq_client, fsid_type, fsidv, &rqstp->rq_chandle);
	if (PTR_ERR(exp) == -ENOENT)
		goto gss;
	if (IS_ERR(exp))
		return exp;
	/* If it has secinfo, assume there are no gss/... clients */
	if (exp->ex_nflavors > 0)
		return exp;
gss:
	/* Otherwise, try falling back on gss client */
	if (rqstp->rq_gssclient == NULL)
		return exp;
	gssexp = exp_find(rqstp->rq_gssclient, fsid_type, fsidv,
						&rqstp->rq_chandle);
	if (PTR_ERR(gssexp) == -ENOENT)
		return exp;
	if (!IS_ERR(exp))
		exp_put(exp);
	return gssexp;
}