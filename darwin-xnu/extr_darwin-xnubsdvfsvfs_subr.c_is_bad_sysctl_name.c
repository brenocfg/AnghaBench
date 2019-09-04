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
struct vfstable {int /*<<< orphan*/  vfc_name; } ;

/* Variables and functions */
#define  AFPFS_VFS_CTL_GETID 140 
#define  AFPFS_VFS_CTL_NETCHANGE 139 
#define  AFPFS_VFS_CTL_VOLCHANGE 138 
#define  SMBFS_SYSCTL_GET_SERVER_SHARE 137 
#define  SMBFS_SYSCTL_REMOUNT 136 
#define  SMBFS_SYSCTL_REMOUNT_INFO 135 
#define  VFS_CTL_DISC 134 
#define  VFS_CTL_NOLOCKS 133 
#define  VFS_CTL_NSTATUS 132 
#define  VFS_CTL_QUERY 131 
#define  VFS_CTL_SADDR 130 
#define  VFS_CTL_SERVERINFO 129 
#define  VFS_CTL_TIMEO 128 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
is_bad_sysctl_name(struct vfstable *vfsp, int selector_name)
{
	switch(selector_name) {
		case VFS_CTL_QUERY:
		case VFS_CTL_TIMEO:
		case VFS_CTL_NOLOCKS:
		case VFS_CTL_NSTATUS:
		case VFS_CTL_SADDR:
		case VFS_CTL_DISC:
		case VFS_CTL_SERVERINFO:
			return 1;

		default:
			break;
	}

	// the more complicated check for some of SMB's special values
	if (strcmp(vfsp->vfc_name, "smbfs") == 0) {
		switch(selector_name) {
			case SMBFS_SYSCTL_REMOUNT:
			case SMBFS_SYSCTL_REMOUNT_INFO:
			case SMBFS_SYSCTL_GET_SERVER_SHARE:
				return 1;
		}
	} else if (strcmp(vfsp->vfc_name, "afpfs") == 0) {
		switch(selector_name) {
			case AFPFS_VFS_CTL_GETID:
			case AFPFS_VFS_CTL_NETCHANGE:
			case AFPFS_VFS_CTL_VOLCHANGE:
				return 1;
		}
	}

	//
	// If we get here we passed all the checks so the selector is ok
	//
	return 0;
}