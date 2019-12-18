#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct svc_rqst {int dummy; } ;
struct svc_fh {scalar_t__ fh_dentry; } ;
struct TYPE_3__ {scalar_t__ fh_dentry; } ;
struct nfsd4_compound_state {TYPE_1__ current_fh; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  NFS4_FHSIZE ; 
 scalar_t__ exp_pseudoroot (struct svc_rqst*,struct svc_fh*) ; 
 int /*<<< orphan*/  fh_init (struct svc_fh*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fh_put (struct svc_fh*) ; 
 scalar_t__ nfsd_lookup (struct svc_rqst*,TYPE_1__*,char*,int,TYPE_1__*) ; 
 scalar_t__ nfserr_noent ; 

__attribute__((used)) static __be32
nfsd4_lookupp(struct svc_rqst *rqstp, struct nfsd4_compound_state *cstate,
	      void *arg)
{
	struct svc_fh tmp_fh;
	__be32 ret;

	fh_init(&tmp_fh, NFS4_FHSIZE);
	ret = exp_pseudoroot(rqstp, &tmp_fh);
	if (ret)
		return ret;
	if (tmp_fh.fh_dentry == cstate->current_fh.fh_dentry) {
		fh_put(&tmp_fh);
		return nfserr_noent;
	}
	fh_put(&tmp_fh);
	return nfsd_lookup(rqstp, &cstate->current_fh,
			   "..", 2, &cstate->current_fh);
}