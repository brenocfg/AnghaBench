#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_6__ {scalar_t__ minor; void* major; } ;
struct TYPE_4__ {void* blocks; void* blocksize; } ;
struct TYPE_5__ {TYPE_1__ nfs2; } ;
struct nfs_fattr {int mode; int /*<<< orphan*/  rdev; int /*<<< orphan*/  valid; int /*<<< orphan*/  ctime; int /*<<< orphan*/  change_attr; int /*<<< orphan*/  mtime; int /*<<< orphan*/  atime; void* fileid; TYPE_3__ fsid; TYPE_2__ du; void* size; void* gid; void* uid; void* nlink; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 scalar_t__ NFCHR ; 
 scalar_t__ NFS2_FIFO_DEV ; 
 int /*<<< orphan*/  NFS_ATTR_FATTR_V2 ; 
 int S_IFIFO ; 
 int S_IFMT ; 
 int /*<<< orphan*/  new_decode_dev (scalar_t__) ; 
 int /*<<< orphan*/  nfs_timespec_to_change_attr (int /*<<< orphan*/ *) ; 
 void* ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xdr_decode_time (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __be32 *
xdr_decode_fattr(__be32 *p, struct nfs_fattr *fattr)
{
	u32 rdev, type;
	type = ntohl(*p++);
	fattr->mode = ntohl(*p++);
	fattr->nlink = ntohl(*p++);
	fattr->uid = ntohl(*p++);
	fattr->gid = ntohl(*p++);
	fattr->size = ntohl(*p++);
	fattr->du.nfs2.blocksize = ntohl(*p++);
	rdev = ntohl(*p++);
	fattr->du.nfs2.blocks = ntohl(*p++);
	fattr->fsid.major = ntohl(*p++);
	fattr->fsid.minor = 0;
	fattr->fileid = ntohl(*p++);
	p = xdr_decode_time(p, &fattr->atime);
	p = xdr_decode_time(p, &fattr->mtime);
	p = xdr_decode_time(p, &fattr->ctime);
	fattr->change_attr = nfs_timespec_to_change_attr(&fattr->ctime);
	fattr->valid |= NFS_ATTR_FATTR_V2;
	fattr->rdev = new_decode_dev(rdev);
	if (type == NFCHR && rdev == NFS2_FIFO_DEV) {
		fattr->mode = (fattr->mode & ~S_IFMT) | S_IFIFO;
		fattr->rdev = 0;
	}
	return p;
}