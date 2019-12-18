#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct key {int dummy; } ;
struct afs_volume_status {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  unique; int /*<<< orphan*/  vnode; int /*<<< orphan*/  vid; } ;
struct afs_vnode {TYPE_1__ fid; TYPE_4__* volume; } ;
struct TYPE_7__ {int /*<<< orphan*/  s_addr; } ;
struct afs_server {TYPE_2__ addr; } ;
struct TYPE_8__ {int /*<<< orphan*/  name; } ;
struct TYPE_10__ {TYPE_3__ vldb; } ;
struct TYPE_9__ {TYPE_5__* vlocation; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct afs_server*) ; 
 int PTR_ERR (struct afs_server*) ; 
 int /*<<< orphan*/  _debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _leave (char*,int) ; 
 int afs_fs_get_volume_status (struct afs_server*,struct key*,struct afs_vnode*,struct afs_volume_status*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  afs_put_server (struct afs_server*) ; 
 int /*<<< orphan*/  afs_sync_call ; 
 struct afs_server* afs_volume_pick_fileserver (struct afs_vnode*) ; 
 int /*<<< orphan*/  afs_volume_release_fileserver (struct afs_vnode*,struct afs_server*,int) ; 
 int /*<<< orphan*/  key_serial (struct key*) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 

int afs_vnode_get_volume_status(struct afs_vnode *vnode, struct key *key,
				struct afs_volume_status *vs)
{
	struct afs_server *server;
	int ret;

	_enter("%s{%x:%u.%u},%x,",
	       vnode->volume->vlocation->vldb.name,
	       vnode->fid.vid,
	       vnode->fid.vnode,
	       vnode->fid.unique,
	       key_serial(key));

	do {
		/* pick a server to query */
		server = afs_volume_pick_fileserver(vnode);
		if (IS_ERR(server))
			goto no_server;

		_debug("USING SERVER: %08x\n", ntohl(server->addr.s_addr));

		ret = afs_fs_get_volume_status(server, key, vnode, vs, &afs_sync_call);

	} while (!afs_volume_release_fileserver(vnode, server, ret));

	/* adjust the flags */
	if (ret == 0)
		afs_put_server(server);

	_leave(" = %d", ret);
	return ret;

no_server:
	return PTR_ERR(server);
}