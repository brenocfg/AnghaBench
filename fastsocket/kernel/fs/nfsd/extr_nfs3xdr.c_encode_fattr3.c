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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct svc_rqst {int dummy; } ;
struct svc_fh {int dummy; } ;
struct kstat {int mode; scalar_t__ size; int ino; int /*<<< orphan*/  ctime; int /*<<< orphan*/  mtime; int /*<<< orphan*/  atime; int /*<<< orphan*/  rdev; scalar_t__ blocks; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; scalar_t__ nlink; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 scalar_t__ MAJOR (int /*<<< orphan*/ ) ; 
 scalar_t__ MINOR (int /*<<< orphan*/ ) ; 
 scalar_t__ NFS3_MAXPATHLEN ; 
 int S_IFMT ; 
 scalar_t__ S_ISLNK (int) ; 
 int /*<<< orphan*/ * encode_fsid (int /*<<< orphan*/ *,struct svc_fh*) ; 
 int /*<<< orphan*/ * encode_time3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nfs3_ftypes ; 
 scalar_t__ nfsd_rgid (struct svc_rqst*,int /*<<< orphan*/ ) ; 
 scalar_t__ nfsd_ruid (struct svc_rqst*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xdr_encode_hyper (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static __be32 *
encode_fattr3(struct svc_rqst *rqstp, __be32 *p, struct svc_fh *fhp,
	      struct kstat *stat)
{
	*p++ = htonl(nfs3_ftypes[(stat->mode & S_IFMT) >> 12]);
	*p++ = htonl((u32) stat->mode);
	*p++ = htonl((u32) stat->nlink);
	*p++ = htonl((u32) nfsd_ruid(rqstp, stat->uid));
	*p++ = htonl((u32) nfsd_rgid(rqstp, stat->gid));
	if (S_ISLNK(stat->mode) && stat->size > NFS3_MAXPATHLEN) {
		p = xdr_encode_hyper(p, (u64) NFS3_MAXPATHLEN);
	} else {
		p = xdr_encode_hyper(p, (u64) stat->size);
	}
	p = xdr_encode_hyper(p, ((u64)stat->blocks) << 9);
	*p++ = htonl((u32) MAJOR(stat->rdev));
	*p++ = htonl((u32) MINOR(stat->rdev));
	p = encode_fsid(p, fhp);
	p = xdr_encode_hyper(p, stat->ino);
	p = encode_time3(p, &stat->atime);
	p = encode_time3(p, &stat->mtime);
	p = encode_time3(p, &stat->ctime);

	return p;
}