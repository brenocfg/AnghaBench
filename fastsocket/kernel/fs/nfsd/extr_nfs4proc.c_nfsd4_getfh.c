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
struct svc_fh {int /*<<< orphan*/  fh_dentry; } ;
struct nfsd4_compound_state {struct svc_fh current_fh; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  nfs_ok ; 
 int /*<<< orphan*/  nfserr_nofilehandle ; 

__attribute__((used)) static __be32
nfsd4_getfh(struct svc_rqst *rqstp, struct nfsd4_compound_state *cstate,
	    struct svc_fh **getfh)
{
	if (!cstate->current_fh.fh_dentry)
		return nfserr_nofilehandle;

	*getfh = &cstate->current_fh;
	return nfs_ok;
}