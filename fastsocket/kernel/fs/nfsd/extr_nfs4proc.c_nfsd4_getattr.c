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
struct svc_rqst {int dummy; } ;
struct nfsd4_getattr {int* ga_bmval; int /*<<< orphan*/ * ga_fhp; } ;
struct nfsd4_compound_state {int /*<<< orphan*/  current_fh; int /*<<< orphan*/  minorversion; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  NFSD_MAY_NOP ; 
 int NFSD_WRITEONLY_ATTRS_WORD1 ; 
 scalar_t__ fh_verify (struct svc_rqst*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nfs_ok ; 
 int nfsd_suppattrs0 (int /*<<< orphan*/ ) ; 
 int nfsd_suppattrs1 (int /*<<< orphan*/ ) ; 
 int nfsd_suppattrs2 (int /*<<< orphan*/ ) ; 
 scalar_t__ nfserr_inval ; 

__attribute__((used)) static __be32
nfsd4_getattr(struct svc_rqst *rqstp, struct nfsd4_compound_state *cstate,
	      struct nfsd4_getattr *getattr)
{
	__be32 status;

	status = fh_verify(rqstp, &cstate->current_fh, 0, NFSD_MAY_NOP);
	if (status)
		return status;

	if (getattr->ga_bmval[1] & NFSD_WRITEONLY_ATTRS_WORD1)
		return nfserr_inval;

	getattr->ga_bmval[0] &= nfsd_suppattrs0(cstate->minorversion);
	getattr->ga_bmval[1] &= nfsd_suppattrs1(cstate->minorversion);
	getattr->ga_bmval[2] &= nfsd_suppattrs2(cstate->minorversion);

	getattr->ga_fhp = &cstate->current_fh;
	return nfs_ok;
}