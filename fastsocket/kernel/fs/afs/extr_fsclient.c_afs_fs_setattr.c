#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct key {int dummy; } ;
struct iattr {int ia_valid; } ;
struct afs_wait_mode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  unique; int /*<<< orphan*/  vnode; int /*<<< orphan*/  vid; } ;
struct afs_vnode {TYPE_1__ fid; } ;
struct afs_server {int /*<<< orphan*/  addr; } ;
struct afs_call {int /*<<< orphan*/ * request; int /*<<< orphan*/  operation_ID; int /*<<< orphan*/  port; int /*<<< orphan*/  service_id; struct afs_vnode* reply; struct key* key; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  AFS_FS_PORT ; 
 int ATTR_SIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FSSTORESTATUS ; 
 int /*<<< orphan*/  FS_SERVICE ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  afs_RXFSStoreStatus ; 
 struct afs_call* afs_alloc_flat_call (int /*<<< orphan*/ *,int,int) ; 
 int afs_fs_setattr_size (struct afs_server*,struct key*,struct afs_vnode*,struct iattr*,struct afs_wait_mode const*) ; 
 int afs_make_call (int /*<<< orphan*/ *,struct afs_call*,int /*<<< orphan*/ ,struct afs_wait_mode const*) ; 
 void* htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_serial (struct key*) ; 
 int /*<<< orphan*/  xdr_encode_AFS_StoreStatus (int /*<<< orphan*/ **,struct iattr*) ; 

int afs_fs_setattr(struct afs_server *server, struct key *key,
		   struct afs_vnode *vnode, struct iattr *attr,
		   const struct afs_wait_mode *wait_mode)
{
	struct afs_call *call;
	__be32 *bp;

	if (attr->ia_valid & ATTR_SIZE)
		return afs_fs_setattr_size(server, key, vnode, attr,
					   wait_mode);

	_enter(",%x,{%x:%u},,",
	       key_serial(key), vnode->fid.vid, vnode->fid.vnode);

	call = afs_alloc_flat_call(&afs_RXFSStoreStatus,
				   (4 + 6) * 4,
				   (21 + 6) * 4);
	if (!call)
		return -ENOMEM;

	call->key = key;
	call->reply = vnode;
	call->service_id = FS_SERVICE;
	call->port = htons(AFS_FS_PORT);
	call->operation_ID = FSSTORESTATUS;

	/* marshall the parameters */
	bp = call->request;
	*bp++ = htonl(FSSTORESTATUS);
	*bp++ = htonl(vnode->fid.vid);
	*bp++ = htonl(vnode->fid.vnode);
	*bp++ = htonl(vnode->fid.unique);

	xdr_encode_AFS_StoreStatus(&bp, attr);

	return afs_make_call(&server->addr, call, GFP_NOFS, wait_mode);
}