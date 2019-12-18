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
typedef  int /*<<< orphan*/  svc_fh ;
struct svc_rqst {int dummy; } ;
struct nfsd_attrstat {int /*<<< orphan*/  fh; } ;
struct nfsd3_setaclargs {int /*<<< orphan*/  acl_default; int /*<<< orphan*/  acl_access; int /*<<< orphan*/  fh; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_TYPE_ACCESS ; 
 int /*<<< orphan*/  ACL_TYPE_DEFAULT ; 
 int /*<<< orphan*/  NFSD_MAY_SATTR ; 
 int /*<<< orphan*/  SVCFH_fmt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fh_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ fh_verify (struct svc_rqst*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsd_set_posix_acl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nfserrno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  posix_acl_release (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __be32 nfsacld_proc_setacl(struct svc_rqst * rqstp,
		struct nfsd3_setaclargs *argp,
		struct nfsd_attrstat *resp)
{
	svc_fh *fh;
	__be32 nfserr = 0;

	dprintk("nfsd: SETACL(2acl)   %s\n", SVCFH_fmt(&argp->fh));

	fh = fh_copy(&resp->fh, &argp->fh);
	nfserr = fh_verify(rqstp, &resp->fh, 0, NFSD_MAY_SATTR);

	if (!nfserr) {
		nfserr = nfserrno( nfsd_set_posix_acl(
			fh, ACL_TYPE_ACCESS, argp->acl_access) );
	}
	if (!nfserr) {
		nfserr = nfserrno( nfsd_set_posix_acl(
			fh, ACL_TYPE_DEFAULT, argp->acl_default) );
	}

	/* argp->acl_{access,default} may have been allocated in
	   nfssvc_decode_setaclargs. */
	posix_acl_release(argp->acl_access);
	posix_acl_release(argp->acl_default);
	return nfserr;
}