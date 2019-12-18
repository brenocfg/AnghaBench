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
typedef  int /*<<< orphan*/  uid_t ;
typedef  int /*<<< orphan*/  u_long ;
struct TYPE_4__ {int oa_flavor; } ;
struct svc_req {scalar_t__ rq_clntcred; TYPE_2__ rq_cred; } ;
struct authunix_parms {int /*<<< orphan*/  aup_gid; int /*<<< orphan*/  aup_uid; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
struct authdes_cred {TYPE_1__ adc_fullname; } ;
typedef  int /*<<< orphan*/  gid_t ;
typedef  int /*<<< orphan*/  SVCXPRT ;

/* Variables and functions */
#define  AUTH_DES 129 
#define  AUTH_UNIX 128 
 int /*<<< orphan*/  INVALIDID ; 
 int sscanf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svcerr_weakauth (int /*<<< orphan*/ *) ; 

int
getcreds(struct svc_req *rp, uid_t *u, gid_t *g, SVCXPRT *nfsxprt)
{
  struct authunix_parms *aup = (struct authunix_parms *) NULL;
#ifdef HAVE_RPC_AUTH_DES_H
  struct authdes_cred *adp;
#endif /* HAVE_RPC_AUTH_DES_H */

  switch (rp->rq_cred.oa_flavor) {

  case AUTH_UNIX:
    aup = (struct authunix_parms *) rp->rq_clntcred;
    *u = aup->aup_uid;
    *g = aup->aup_gid;
    break;

#ifdef HAVE_RPC_AUTH_DES_H
  case AUTH_DES:
    adp = (struct authdes_cred *) rp->rq_clntcred;
    *g = INVALIDID;		/* some unknown group id */
    if (sscanf(adp->adc_fullname.name, "unix.%lu@", (u_long *) u) == 1)
        break;
    /* fall through */
#endif /* HAVE_RPC_AUTH_DES_H */

  default:
    *u = *g = INVALIDID;	/* just in case */
    svcerr_weakauth(nfsxprt);
    return -1;
  }

  return 0;			/* everything is ok */
}