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
typedef  int /*<<< orphan*/  u32 ;
struct svc_rqst {int dummy; } ;
struct nfsd4_compound_state {int /*<<< orphan*/  current_fh; } ;
struct TYPE_3__ {scalar_t__ data; } ;
struct nfsd4_commit {int /*<<< orphan*/  co_count; int /*<<< orphan*/  co_offset; TYPE_1__ co_verf; } ;
typedef  scalar_t__ __be32 ;
struct TYPE_4__ {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;

/* Variables and functions */
 scalar_t__ nfsd_commit (struct svc_rqst*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nfserr_inval ; 
 scalar_t__ nfserr_symlink ; 
 TYPE_2__ nfssvc_boot ; 

__attribute__((used)) static __be32
nfsd4_commit(struct svc_rqst *rqstp, struct nfsd4_compound_state *cstate,
	     struct nfsd4_commit *commit)
{
	__be32 status;

	u32 *p = (u32 *)commit->co_verf.data;
	*p++ = nfssvc_boot.tv_sec;
	*p++ = nfssvc_boot.tv_usec;

	status = nfsd_commit(rqstp, &cstate->current_fh, commit->co_offset,
			     commit->co_count);
	if (status == nfserr_symlink)
		status = nfserr_inval;
	return status;
}