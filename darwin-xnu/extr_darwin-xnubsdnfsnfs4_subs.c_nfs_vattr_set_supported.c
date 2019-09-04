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
typedef  int /*<<< orphan*/  uint32_t ;
struct vnode_attr {int dummy; } ;

/* Variables and functions */
 scalar_t__ NFS_BITMAP_ISSET (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFS_FATTR_ACL ; 
 int /*<<< orphan*/  NFS_FATTR_ARCHIVE ; 
 int /*<<< orphan*/  NFS_FATTR_FILEID ; 
 int /*<<< orphan*/  NFS_FATTR_FSID ; 
 int /*<<< orphan*/  NFS_FATTR_HIDDEN ; 
 int /*<<< orphan*/  NFS_FATTR_MODE ; 
 int /*<<< orphan*/  NFS_FATTR_NUMLINKS ; 
 int /*<<< orphan*/  NFS_FATTR_OWNER ; 
 int /*<<< orphan*/  NFS_FATTR_OWNER_GROUP ; 
 int /*<<< orphan*/  NFS_FATTR_RAWDEV ; 
 int /*<<< orphan*/  NFS_FATTR_SIZE ; 
 int /*<<< orphan*/  NFS_FATTR_SPACE_USED ; 
 int /*<<< orphan*/  NFS_FATTR_TIME_ACCESS ; 
 int /*<<< orphan*/  NFS_FATTR_TIME_BACKUP ; 
 int /*<<< orphan*/  NFS_FATTR_TIME_CREATE ; 
 int /*<<< orphan*/  NFS_FATTR_TIME_METADATA ; 
 int /*<<< orphan*/  NFS_FATTR_TIME_MODIFY ; 
 int /*<<< orphan*/  NFS_FATTR_TYPE ; 
 int /*<<< orphan*/  VATTR_SET_SUPPORTED (struct vnode_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  va_access_time ; 
 int /*<<< orphan*/  va_acl ; 
 int /*<<< orphan*/  va_backup_time ; 
 int /*<<< orphan*/  va_change_time ; 
 int /*<<< orphan*/  va_create_time ; 
 int /*<<< orphan*/  va_data_size ; 
 int /*<<< orphan*/  va_fileid ; 
 int /*<<< orphan*/  va_flags ; 
 int /*<<< orphan*/  va_fsid ; 
 int /*<<< orphan*/  va_gid ; 
 int /*<<< orphan*/  va_guuid ; 
 int /*<<< orphan*/  va_mode ; 
 int /*<<< orphan*/  va_modify_time ; 
 int /*<<< orphan*/  va_nlink ; 
 int /*<<< orphan*/  va_rdev ; 
 int /*<<< orphan*/  va_total_alloc ; 
 int /*<<< orphan*/  va_type ; 
 int /*<<< orphan*/  va_uid ; 
 int /*<<< orphan*/  va_uuuid ; 

void
nfs_vattr_set_supported(uint32_t *bitmap, struct vnode_attr *vap)
{
	if (NFS_BITMAP_ISSET(bitmap, NFS_FATTR_TYPE))
		VATTR_SET_SUPPORTED(vap, va_type);
	// if (NFS_BITMAP_ISSET(bitmap, NFS_FATTR_CHANGE))
	if (NFS_BITMAP_ISSET(bitmap, NFS_FATTR_SIZE))
		VATTR_SET_SUPPORTED(vap, va_data_size);
	if (NFS_BITMAP_ISSET(bitmap, NFS_FATTR_FSID))
		VATTR_SET_SUPPORTED(vap, va_fsid);
	if (NFS_BITMAP_ISSET(bitmap, NFS_FATTR_ACL))
		VATTR_SET_SUPPORTED(vap, va_acl);
	if (NFS_BITMAP_ISSET(bitmap, NFS_FATTR_ARCHIVE))
		VATTR_SET_SUPPORTED(vap, va_flags);
	if (NFS_BITMAP_ISSET(bitmap, NFS_FATTR_FILEID))
		VATTR_SET_SUPPORTED(vap, va_fileid);
	if (NFS_BITMAP_ISSET(bitmap, NFS_FATTR_HIDDEN))
		VATTR_SET_SUPPORTED(vap, va_flags);
	// if (NFS_BITMAP_ISSET(bitmap, NFS_FATTR_MIMETYPE))
	if (NFS_BITMAP_ISSET(bitmap, NFS_FATTR_MODE))
		VATTR_SET_SUPPORTED(vap, va_mode);
	if (NFS_BITMAP_ISSET(bitmap, NFS_FATTR_NUMLINKS))
		VATTR_SET_SUPPORTED(vap, va_nlink);
	if (NFS_BITMAP_ISSET(bitmap, NFS_FATTR_OWNER)) {
		VATTR_SET_SUPPORTED(vap, va_uid);
		VATTR_SET_SUPPORTED(vap, va_uuuid);
	}
	if (NFS_BITMAP_ISSET(bitmap, NFS_FATTR_OWNER_GROUP)) {
		VATTR_SET_SUPPORTED(vap, va_gid);
		VATTR_SET_SUPPORTED(vap, va_guuid);
	}
	if (NFS_BITMAP_ISSET(bitmap, NFS_FATTR_RAWDEV))
		VATTR_SET_SUPPORTED(vap, va_rdev);
	if (NFS_BITMAP_ISSET(bitmap, NFS_FATTR_SPACE_USED))
		VATTR_SET_SUPPORTED(vap, va_total_alloc);
	// if (NFS_BITMAP_ISSET(bitmap, NFS_FATTR_SYSTEM))
	if (NFS_BITMAP_ISSET(bitmap, NFS_FATTR_TIME_ACCESS))
		VATTR_SET_SUPPORTED(vap, va_access_time);
	if (NFS_BITMAP_ISSET(bitmap, NFS_FATTR_TIME_BACKUP))
		VATTR_SET_SUPPORTED(vap, va_backup_time);
	if (NFS_BITMAP_ISSET(bitmap, NFS_FATTR_TIME_CREATE))
		VATTR_SET_SUPPORTED(vap, va_create_time);
	if (NFS_BITMAP_ISSET(bitmap, NFS_FATTR_TIME_METADATA))
		VATTR_SET_SUPPORTED(vap, va_change_time);
	if (NFS_BITMAP_ISSET(bitmap, NFS_FATTR_TIME_MODIFY))
		VATTR_SET_SUPPORTED(vap, va_modify_time);
}