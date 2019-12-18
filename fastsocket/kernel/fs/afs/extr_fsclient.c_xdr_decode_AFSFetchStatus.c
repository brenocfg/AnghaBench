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
typedef  int /*<<< orphan*/  umode_t ;
typedef  int u64 ;
typedef  int u32 ;
struct TYPE_7__ {int /*<<< orphan*/  vnode; int /*<<< orphan*/  vid; int /*<<< orphan*/  unique; } ;
struct TYPE_6__ {void* tv_sec; } ;
struct TYPE_8__ {TYPE_2__ i_ctime; TYPE_2__ i_atime; TYPE_2__ i_mtime; int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_nlink; int /*<<< orphan*/  i_version; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; } ;
struct afs_vnode {int /*<<< orphan*/  flags; TYPE_3__ fid; TYPE_4__ vfs_inode; } ;
struct TYPE_5__ {int /*<<< orphan*/  vid; int /*<<< orphan*/  unique; int /*<<< orphan*/  vnode; } ;
struct afs_file_status {int size; int data_version; void* mtime_server; int /*<<< orphan*/  mode; int /*<<< orphan*/  nlink; int /*<<< orphan*/  group; int /*<<< orphan*/  owner; TYPE_1__ parent; void* mtime_client; int /*<<< orphan*/  lock_count; int /*<<< orphan*/  anon_access; int /*<<< orphan*/  caller_access; int /*<<< orphan*/  author; int /*<<< orphan*/  type; void* if_version; } ;
typedef  int afs_dataversion_t ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  AFS_VNODE_MODIFIED ; 
 int /*<<< orphan*/  AFS_VNODE_UNSET ; 
 int /*<<< orphan*/  AFS_VNODE_ZAP_DATA ; 
 int /*<<< orphan*/  EXTRACT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_IALLUGO ; 
 int /*<<< orphan*/  _debug (char*,...) ; 
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  i_size_write (TYPE_4__*,int) ; 
 void* ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void xdr_decode_AFSFetchStatus(const __be32 **_bp,
				      struct afs_file_status *status,
				      struct afs_vnode *vnode,
				      afs_dataversion_t *store_version)
{
	afs_dataversion_t expected_version;
	const __be32 *bp = *_bp;
	umode_t mode;
	u64 data_version, size;
	u32 changed = 0; /* becomes non-zero if ctime-type changes seen */

#define EXTRACT(DST)				\
	do {					\
		u32 x = ntohl(*bp++);		\
		changed |= DST - x;		\
		DST = x;			\
	} while (0)

	status->if_version = ntohl(*bp++);
	EXTRACT(status->type);
	EXTRACT(status->nlink);
	size = ntohl(*bp++);
	data_version = ntohl(*bp++);
	EXTRACT(status->author);
	EXTRACT(status->owner);
	EXTRACT(status->caller_access); /* call ticket dependent */
	EXTRACT(status->anon_access);
	EXTRACT(status->mode);
	EXTRACT(status->parent.vnode);
	EXTRACT(status->parent.unique);
	bp++; /* seg size */
	status->mtime_client = ntohl(*bp++);
	status->mtime_server = ntohl(*bp++);
	EXTRACT(status->group);
	bp++; /* sync counter */
	data_version |= (u64) ntohl(*bp++) << 32;
	EXTRACT(status->lock_count);
	size |= (u64) ntohl(*bp++) << 32;
	bp++; /* spare 4 */
	*_bp = bp;

	if (size != status->size) {
		status->size = size;
		changed |= true;
	}
	status->mode &= S_IALLUGO;

	_debug("vnode time %lx, %lx",
	       status->mtime_client, status->mtime_server);

	if (vnode) {
		status->parent.vid = vnode->fid.vid;
		if (changed && !test_bit(AFS_VNODE_UNSET, &vnode->flags)) {
			_debug("vnode changed");
			i_size_write(&vnode->vfs_inode, size);
			vnode->vfs_inode.i_uid = status->owner;
			vnode->vfs_inode.i_gid = status->group;
			vnode->vfs_inode.i_version = vnode->fid.unique;
			vnode->vfs_inode.i_nlink = status->nlink;

			mode = vnode->vfs_inode.i_mode;
			mode &= ~S_IALLUGO;
			mode |= status->mode;
			barrier();
			vnode->vfs_inode.i_mode = mode;
		}

		vnode->vfs_inode.i_ctime.tv_sec	= status->mtime_server;
		vnode->vfs_inode.i_mtime	= vnode->vfs_inode.i_ctime;
		vnode->vfs_inode.i_atime	= vnode->vfs_inode.i_ctime;
	}

	expected_version = status->data_version;
	if (store_version)
		expected_version = *store_version;

	if (expected_version != data_version) {
		status->data_version = data_version;
		if (vnode && !test_bit(AFS_VNODE_UNSET, &vnode->flags)) {
			_debug("vnode modified %llx on {%x:%u}",
			       (unsigned long long) data_version,
			       vnode->fid.vid, vnode->fid.vnode);
			set_bit(AFS_VNODE_MODIFIED, &vnode->flags);
			set_bit(AFS_VNODE_ZAP_DATA, &vnode->flags);
		}
	} else if (store_version) {
		status->data_version = data_version;
	}
}