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
struct vnode_attr {int va_type; } ;
typedef  int /*<<< orphan*/ * mount_t ;

/* Variables and functions */
 int EACCES ; 
 int /*<<< orphan*/  KAUTH_DEBUG (char*,int /*<<< orphan*/ ) ; 
 int KAUTH_VNODE_ADD_FILE ; 
 int KAUTH_VNODE_ADD_SUBDIRECTORY ; 
 int KAUTH_VNODE_APPEND_DATA ; 
 int KAUTH_VNODE_WRITE_DATA ; 
 int KAUTH_VNODE_WRITE_EXTATTRIBUTES ; 
 int KAUTH_VNODE_WRITE_RIGHTS ; 
 int MNT_NOUSERXATTR ; 
#define  VBLK 131 
#define  VCHR 130 
 int VDIR ; 
#define  VFIFO 129 
#define  VSOCK 128 
 int vfs_flags (int /*<<< orphan*/ *) ; 
 int vnode_immutable (struct vnode_attr*,int,int) ; 
 int /*<<< orphan*/  vp ; 

__attribute__((used)) static int
vnode_authorize_checkimmutable(mount_t mp, struct vnode_attr *vap, int rights, int ignore)
{
	int error;
	int append;

	/*
	 * Perform immutability checks for operations that change data.
	 *
	 * Sockets, fifos and devices require special handling.
	 */
	switch(vap->va_type) {
	case VSOCK:
	case VFIFO:
	case VBLK:
	case VCHR:
		/*
		 * Writing to these nodes does not change the filesystem data,
		 * so forget that it's being tried.
		 */
		rights &= ~KAUTH_VNODE_WRITE_DATA;
		break;
	default:
		break;
	}

	error = 0;
	if (rights & KAUTH_VNODE_WRITE_RIGHTS) {
		
		/* check per-filesystem options if possible */
		if (mp != NULL) {
	
			/* check for no-EA filesystems */
			if ((rights & KAUTH_VNODE_WRITE_EXTATTRIBUTES) &&
			    (vfs_flags(mp) & MNT_NOUSERXATTR)) {
				KAUTH_DEBUG("%p    DENIED - filesystem disallowed extended attributes", vp);
				error = EACCES;  /* User attributes disabled */
				goto out;
			}
		}

		/* 
		 * check for file immutability. first, check if the requested rights are 
		 * allowable for a UF_APPEND file.
		 */
		append = 0;
		if (vap->va_type == VDIR) {
			if ((rights & (KAUTH_VNODE_ADD_FILE | KAUTH_VNODE_ADD_SUBDIRECTORY | KAUTH_VNODE_WRITE_EXTATTRIBUTES)) == rights)
				append = 1;
		} else {
			if ((rights & (KAUTH_VNODE_APPEND_DATA | KAUTH_VNODE_WRITE_EXTATTRIBUTES)) == rights)
				append = 1;
		}
		if ((error = vnode_immutable(vap, append, ignore)) != 0) {
			KAUTH_DEBUG("%p    DENIED - file is immutable", vp);
			goto out;
		}
	}
out:
	return(error);
}