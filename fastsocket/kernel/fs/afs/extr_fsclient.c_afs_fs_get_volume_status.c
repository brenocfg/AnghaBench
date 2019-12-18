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
struct afs_wait_mode {int dummy; } ;
struct afs_volume_status {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  vid; } ;
struct afs_vnode {TYPE_1__ fid; } ;
struct afs_server {int /*<<< orphan*/  addr; } ;
struct afs_call {int /*<<< orphan*/ * request; int /*<<< orphan*/  port; int /*<<< orphan*/  service_id; void* reply3; struct afs_volume_status* reply2; struct afs_vnode* reply; struct key* key; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  AFSOPAQUEMAX ; 
 int /*<<< orphan*/  AFS_FS_PORT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FSGETVOLUMESTATUS ; 
 int /*<<< orphan*/  FS_SERVICE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  _enter (char*) ; 
 int /*<<< orphan*/  afs_RXFSGetVolumeStatus ; 
 struct afs_call* afs_alloc_flat_call (int /*<<< orphan*/ *,int,int) ; 
 int afs_make_call (int /*<<< orphan*/ *,struct afs_call*,int /*<<< orphan*/ ,struct afs_wait_mode const*) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int afs_fs_get_volume_status(struct afs_server *server,
			     struct key *key,
			     struct afs_vnode *vnode,
			     struct afs_volume_status *vs,
			     const struct afs_wait_mode *wait_mode)
{
	struct afs_call *call;
	__be32 *bp;
	void *tmpbuf;

	_enter("");

	tmpbuf = kmalloc(AFSOPAQUEMAX, GFP_KERNEL);
	if (!tmpbuf)
		return -ENOMEM;

	call = afs_alloc_flat_call(&afs_RXFSGetVolumeStatus, 2 * 4, 12 * 4);
	if (!call) {
		kfree(tmpbuf);
		return -ENOMEM;
	}

	call->key = key;
	call->reply = vnode;
	call->reply2 = vs;
	call->reply3 = tmpbuf;
	call->service_id = FS_SERVICE;
	call->port = htons(AFS_FS_PORT);

	/* marshall the parameters */
	bp = call->request;
	bp[0] = htonl(FSGETVOLUMESTATUS);
	bp[1] = htonl(vnode->fid.vid);

	return afs_make_call(&server->addr, call, GFP_NOFS, wait_mode);
}