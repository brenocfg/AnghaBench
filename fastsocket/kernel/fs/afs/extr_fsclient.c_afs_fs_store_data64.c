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
typedef  int u32 ;
struct afs_writeback {int /*<<< orphan*/  key; struct afs_vnode* vnode; } ;
struct afs_wait_mode {int dummy; } ;
struct TYPE_6__ {int vid; int vnode; int unique; } ;
struct TYPE_5__ {scalar_t__ data_version; } ;
struct TYPE_4__ {int /*<<< orphan*/  i_mapping; } ;
struct afs_vnode {TYPE_3__ fid; TYPE_2__ status; TYPE_1__ vfs_inode; } ;
struct afs_server {int /*<<< orphan*/  addr; } ;
struct afs_call {unsigned int first_offset; unsigned int last_to; int send_pages; int /*<<< orphan*/ * request; scalar_t__ store_version; void* last; void* first; int /*<<< orphan*/  mapping; int /*<<< orphan*/  port; int /*<<< orphan*/  service_id; struct afs_vnode* reply; int /*<<< orphan*/  key; struct afs_writeback* wb; } ;
typedef  void* pgoff_t ;
typedef  int loff_t ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  AFS_FS_PORT ; 
 int ENOMEM ; 
 int FSSTOREDATA64 ; 
 int /*<<< orphan*/  FS_SERVICE ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  afs_RXFSStoreData64 ; 
 struct afs_call* afs_alloc_flat_call (int /*<<< orphan*/ *,int,int) ; 
 int afs_make_call (int /*<<< orphan*/ *,struct afs_call*,int /*<<< orphan*/ ,struct afs_wait_mode const*) ; 
 void* htonl (int) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_serial (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int afs_fs_store_data64(struct afs_server *server,
			       struct afs_writeback *wb,
			       pgoff_t first, pgoff_t last,
			       unsigned offset, unsigned to,
			       loff_t size, loff_t pos, loff_t i_size,
			       const struct afs_wait_mode *wait_mode)
{
	struct afs_vnode *vnode = wb->vnode;
	struct afs_call *call;
	__be32 *bp;

	_enter(",%x,{%x:%u},,",
	       key_serial(wb->key), vnode->fid.vid, vnode->fid.vnode);

	call = afs_alloc_flat_call(&afs_RXFSStoreData64,
				   (4 + 6 + 3 * 2) * 4,
				   (21 + 6) * 4);
	if (!call)
		return -ENOMEM;

	call->wb = wb;
	call->key = wb->key;
	call->reply = vnode;
	call->service_id = FS_SERVICE;
	call->port = htons(AFS_FS_PORT);
	call->mapping = vnode->vfs_inode.i_mapping;
	call->first = first;
	call->last = last;
	call->first_offset = offset;
	call->last_to = to;
	call->send_pages = true;
	call->store_version = vnode->status.data_version + 1;

	/* marshall the parameters */
	bp = call->request;
	*bp++ = htonl(FSSTOREDATA64);
	*bp++ = htonl(vnode->fid.vid);
	*bp++ = htonl(vnode->fid.vnode);
	*bp++ = htonl(vnode->fid.unique);

	*bp++ = 0; /* mask */
	*bp++ = 0; /* mtime */
	*bp++ = 0; /* owner */
	*bp++ = 0; /* group */
	*bp++ = 0; /* unix mode */
	*bp++ = 0; /* segment size */

	*bp++ = htonl(pos >> 32);
	*bp++ = htonl((u32) pos);
	*bp++ = htonl(size >> 32);
	*bp++ = htonl((u32) size);
	*bp++ = htonl(i_size >> 32);
	*bp++ = htonl((u32) i_size);

	return afs_make_call(&server->addr, call, GFP_NOFS, wait_mode);
}