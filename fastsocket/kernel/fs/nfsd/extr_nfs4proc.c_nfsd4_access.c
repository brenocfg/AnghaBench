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
struct nfsd4_compound_state {int /*<<< orphan*/  current_fh; } ;
struct nfsd4_access {int ac_req_access; int ac_resp_access; int /*<<< orphan*/  ac_supported; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int NFS3_ACCESS_FULL ; 
 int /*<<< orphan*/  nfsd_access (struct svc_rqst*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfserr_inval ; 

__attribute__((used)) static __be32
nfsd4_access(struct svc_rqst *rqstp, struct nfsd4_compound_state *cstate,
	     struct nfsd4_access *access)
{
	if (access->ac_req_access & ~NFS3_ACCESS_FULL)
		return nfserr_inval;

	access->ac_resp_access = access->ac_req_access;
	return nfsd_access(rqstp, &cstate->current_fh, &access->ac_resp_access,
			   &access->ac_supported);
}