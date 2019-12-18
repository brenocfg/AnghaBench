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
typedef  int /*<<< orphan*/  u32 ;
struct svc_rqst {int dummy; } ;
struct svc_fh {int dummy; } ;
struct nfs4_file {int /*<<< orphan*/ * fi_fds; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  S_IFREG ; 
 int nfs4_access_to_access (int /*<<< orphan*/ ) ; 
 int nfs4_access_to_omode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs4_file_get_access (struct nfs4_file*,int) ; 
 scalar_t__ nfs_ok ; 
 scalar_t__ nfsd_open (struct svc_rqst*,struct svc_fh*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __be32 nfs4_get_vfs_file(struct svc_rqst *rqstp, struct nfs4_file
*fp, struct svc_fh *cur_fh, u32 nfs4_access)
{
	__be32 status;
	int oflag = nfs4_access_to_omode(nfs4_access);
	int access = nfs4_access_to_access(nfs4_access);

	if (!fp->fi_fds[oflag]) {
		status = nfsd_open(rqstp, cur_fh, S_IFREG, access,
			&fp->fi_fds[oflag]);
		if (status)
			return status;
	}
	nfs4_file_get_access(fp, oflag);

	return nfs_ok;
}