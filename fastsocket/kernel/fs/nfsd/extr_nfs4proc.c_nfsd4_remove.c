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
struct nfsd4_remove {int /*<<< orphan*/  rm_cinfo; int /*<<< orphan*/  rm_namelen; int /*<<< orphan*/  rm_name; } ;
struct nfsd4_compound_state {int /*<<< orphan*/  current_fh; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  fh_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ locks_in_grace () ; 
 scalar_t__ nfsd_unlink (struct svc_rqst*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nfserr_grace ; 
 scalar_t__ nfserr_notdir ; 
 scalar_t__ nfserr_symlink ; 
 int /*<<< orphan*/  set_change_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __be32
nfsd4_remove(struct svc_rqst *rqstp, struct nfsd4_compound_state *cstate,
	     struct nfsd4_remove *remove)
{
	__be32 status;

	if (locks_in_grace())
		return nfserr_grace;
	status = nfsd_unlink(rqstp, &cstate->current_fh, 0,
			     remove->rm_name, remove->rm_namelen);
	if (status == nfserr_symlink)
		return nfserr_notdir;
	if (!status) {
		fh_unlock(&cstate->current_fh);
		set_change_info(&remove->rm_cinfo, &cstate->current_fh);
	}
	return status;
}