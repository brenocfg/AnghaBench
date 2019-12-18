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
struct nfs_fattr {int valid; int /*<<< orphan*/  pre_ctime; int /*<<< orphan*/  pre_mtime; int /*<<< orphan*/  pre_size; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int NFS_ATTR_FATTR_PRECHANGE ; 
 int NFS_ATTR_FATTR_PRECTIME ; 
 int NFS_ATTR_FATTR_PREMTIME ; 
 int NFS_ATTR_FATTR_PRESIZE ; 
 int /*<<< orphan*/ * xdr_decode_hyper (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xdr_decode_time3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline __be32 *
xdr_decode_wcc_attr(__be32 *p, struct nfs_fattr *fattr)
{
	p = xdr_decode_hyper(p, &fattr->pre_size);
	p = xdr_decode_time3(p, &fattr->pre_mtime);
	p = xdr_decode_time3(p, &fattr->pre_ctime);
	fattr->valid |= NFS_ATTR_FATTR_PRESIZE
		| NFS_ATTR_FATTR_PRECHANGE
		| NFS_ATTR_FATTR_PREMTIME
		| NFS_ATTR_FATTR_PRECTIME;
	return p;
}