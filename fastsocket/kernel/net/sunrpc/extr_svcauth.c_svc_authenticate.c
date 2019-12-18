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
struct TYPE_2__ {int /*<<< orphan*/ * head; } ;
struct svc_rqst {struct auth_ops* rq_authop; TYPE_1__ rq_arg; } ;
struct auth_ops {int (* accept ) (struct svc_rqst*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  owner; } ;
typedef  size_t rpc_authflavor_t ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 size_t RPC_AUTH_MAXFLAVOR ; 
 int SVC_DENIED ; 
 struct auth_ops** authtab ; 
 int /*<<< orphan*/  authtab_lock ; 
 int /*<<< orphan*/  dprintk (char*,size_t) ; 
 int /*<<< orphan*/  rpc_auth_ok ; 
 int /*<<< orphan*/  rpc_autherr_badcred ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct svc_rqst*,int /*<<< orphan*/ *) ; 
 size_t svc_getnl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

int
svc_authenticate(struct svc_rqst *rqstp, __be32 *authp)
{
	rpc_authflavor_t	flavor;
	struct auth_ops		*aops;

	*authp = rpc_auth_ok;

	flavor = svc_getnl(&rqstp->rq_arg.head[0]);

	dprintk("svc: svc_authenticate (%d)\n", flavor);

	spin_lock(&authtab_lock);
	if (flavor >= RPC_AUTH_MAXFLAVOR || !(aops = authtab[flavor])
			|| !try_module_get(aops->owner)) {
		spin_unlock(&authtab_lock);
		*authp = rpc_autherr_badcred;
		return SVC_DENIED;
	}
	spin_unlock(&authtab_lock);

	rqstp->rq_authop = aops;
	return aops->accept(rqstp, authp);
}