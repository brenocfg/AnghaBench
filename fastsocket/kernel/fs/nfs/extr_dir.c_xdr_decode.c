#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct xdr_stream {int dummy; } ;
struct nfs_entry {TYPE_4__* fattr; } ;
struct TYPE_11__ {int /*<<< orphan*/  gencount; int /*<<< orphan*/  timestamp; int /*<<< orphan*/  plus; TYPE_3__* file; int /*<<< orphan*/ * (* decode ) (struct xdr_stream*,struct nfs_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_5__ nfs_readdir_descriptor_t ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_10__ {int /*<<< orphan*/  gencount; int /*<<< orphan*/  time_start; } ;
struct TYPE_8__ {TYPE_1__* dentry; } ;
struct TYPE_9__ {TYPE_2__ f_path; } ;
struct TYPE_7__ {int /*<<< orphan*/  d_inode; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NFS_SERVER (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub1 (struct xdr_stream*,struct nfs_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
int xdr_decode(nfs_readdir_descriptor_t *desc, struct nfs_entry *entry, struct xdr_stream *stream)
{
	__be32 *p = desc->decode(stream, entry, NFS_SERVER(desc->file->f_path.dentry->d_inode), desc->plus);
	if (IS_ERR(p))
		return PTR_ERR(p);

	entry->fattr->time_start = desc->timestamp;
	entry->fattr->gencount = desc->gencount;
	return 0;
}