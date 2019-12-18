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
typedef  int /*<<< orphan*/  time_t ;
struct svc_rqst {int dummy; } ;
struct TYPE_2__ {int ia_valid; } ;
struct nfsd4_setattr {TYPE_1__ sa_iattr; int /*<<< orphan*/ * sa_acl; int /*<<< orphan*/  sa_bmval; int /*<<< orphan*/  sa_stateid; } ;
struct nfsd4_compound_state {int /*<<< orphan*/  current_fh; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int ATTR_SIZE ; 
 int /*<<< orphan*/  WR_STATE ; 
 scalar_t__ check_attr_support (struct svc_rqst*,struct nfsd4_compound_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 int /*<<< orphan*/  fh_drop_write (int /*<<< orphan*/ *) ; 
 scalar_t__ fh_want_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs4_lock_state () ; 
 scalar_t__ nfs4_preprocess_stateid_op (struct nfsd4_compound_state*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs4_unlock_state () ; 
 scalar_t__ nfs_ok ; 
 scalar_t__ nfsd4_set_nfs4_acl (struct svc_rqst*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsd_attrmask ; 
 scalar_t__ nfsd_setattr (struct svc_rqst*,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __be32
nfsd4_setattr(struct svc_rqst *rqstp, struct nfsd4_compound_state *cstate,
	      struct nfsd4_setattr *setattr)
{
	__be32 status = nfs_ok;

	if (setattr->sa_iattr.ia_valid & ATTR_SIZE) {
		nfs4_lock_state();
		status = nfs4_preprocess_stateid_op(cstate,
			&setattr->sa_stateid, WR_STATE, NULL);
		nfs4_unlock_state();
		if (status) {
			dprintk("NFSD: nfsd4_setattr: couldn't process stateid!\n");
			return status;
		}
	}
	status = fh_want_write(&cstate->current_fh);
	if (status)
		return status;
	status = nfs_ok;

	status = check_attr_support(rqstp, cstate, setattr->sa_bmval,
				    nfsd_attrmask);
	if (status)
		goto out;

	if (setattr->sa_acl != NULL)
		status = nfsd4_set_nfs4_acl(rqstp, &cstate->current_fh,
					    setattr->sa_acl);
	if (status)
		goto out;
	status = nfsd_setattr(rqstp, &cstate->current_fh, &setattr->sa_iattr,
				0, (time_t)0);
out:
	fh_drop_write(&cstate->current_fh);
	return status;
}