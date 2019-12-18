#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct nfs_page {int /*<<< orphan*/  wb_bytes; TYPE_3__* wb_context; } ;
struct TYPE_8__ {TYPE_1__* i_sb; } ;
struct TYPE_7__ {TYPE_2__* dentry; } ;
struct TYPE_6__ {TYPE_4__* d_inode; } ;
struct TYPE_5__ {int /*<<< orphan*/  s_id; } ;

/* Variables and functions */
 scalar_t__ NFS_FILEID (TYPE_4__*) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,long long,int /*<<< orphan*/ ,long long) ; 
 int /*<<< orphan*/  nfs_release_request (struct nfs_page*) ; 
 scalar_t__ req_offset (struct nfs_page*) ; 

__attribute__((used)) static void nfs_direct_readpage_release(struct nfs_page *req)
{
	dprintk("NFS: direct read done (%s/%lld %d@%lld)\n",
		req->wb_context->dentry->d_inode->i_sb->s_id,
		(long long)NFS_FILEID(req->wb_context->dentry->d_inode),
		req->wb_bytes,
		(long long)req_offset(req));
	nfs_release_request(req);
}