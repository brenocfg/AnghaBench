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
typedef  int /*<<< orphan*/  vnode_t ;
typedef  int /*<<< orphan*/  vfs_context_t ;
typedef  int /*<<< orphan*/  vfa ;
struct TYPE_2__ {int* capabilities; int* valid; } ;
struct vfs_attr {TYPE_1__ f_capabilities; } ;
typedef  int int32_t ;

/* Variables and functions */
 int AD_XATTR_SIZE_BITS ; 
 int /*<<< orphan*/  VFSATTR_INIT (struct vfs_attr*) ; 
 int /*<<< orphan*/  VFSATTR_IS_SUPPORTED (struct vfs_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VFSATTR_WANTED (struct vfs_attr*,int /*<<< orphan*/ ) ; 
 int VNOP_PATHCONF (int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ ) ; 
 size_t VOL_CAPABILITIES_INTERFACES ; 
 int VOL_CAP_INT_EXTENDED_ATTR ; 
#define  _PC_2_SYMLINKS 140 
#define  _PC_ALLOC_SIZE_MIN 139 
#define  _PC_ASYNC_IO 138 
#define  _PC_AUTH_OPAQUE_NP 137 
#define  _PC_EXTENDED_SECURITY_NP 136 
#define  _PC_PRIO_IO 135 
#define  _PC_REC_INCR_XFER_SIZE 134 
#define  _PC_REC_MAX_XFER_SIZE 133 
#define  _PC_REC_MIN_XFER_SIZE 132 
#define  _PC_REC_XFER_ALIGN 131 
#define  _PC_SYMLINK_MAX 130 
#define  _PC_SYNC_IO 129 
#define  _PC_XATTR_SIZE_BITS 128 
 int /*<<< orphan*/  f_capabilities ; 
 int /*<<< orphan*/  memset (struct vfs_attr*,int /*<<< orphan*/ ,int) ; 
 int vfs_authopaque (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_extendedsecurity (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_getattr (int /*<<< orphan*/ ,struct vfs_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_mount (int /*<<< orphan*/ ) ; 

int
vn_pathconf(vnode_t vp, int name, int32_t *retval, vfs_context_t ctx)
{
	int	error = 0;
	struct vfs_attr vfa;

	switch(name) {
	case _PC_EXTENDED_SECURITY_NP:
		*retval = vfs_extendedsecurity(vnode_mount(vp)) ? 1 : 0;
		break;
	case _PC_AUTH_OPAQUE_NP:
		*retval = vfs_authopaque(vnode_mount(vp));
		break;
	case _PC_2_SYMLINKS:
		*retval = 1;	/* XXX NOTSUP on MSDOS, etc. */
		break;
	case _PC_ALLOC_SIZE_MIN:
		*retval = 1;	/* XXX lie: 1 byte */
		break;
	case _PC_ASYNC_IO:	/* unistd.h: _POSIX_ASYNCHRONUS_IO */
		*retval = 1;	/* [AIO] option is supported */
		break;
	case _PC_PRIO_IO:	/* unistd.h: _POSIX_PRIORITIZED_IO */
		*retval = 0;	/* [PIO] option is not supported */
		break;
	case _PC_REC_INCR_XFER_SIZE:
		*retval = 4096;	/* XXX go from MIN to MAX 4K at a time */
		break;
	case _PC_REC_MIN_XFER_SIZE:
		*retval = 4096;	/* XXX recommend 4K minimum reads/writes */
		break;
	case _PC_REC_MAX_XFER_SIZE:
		*retval = 65536; /* XXX recommend 64K maximum reads/writes */
		break;
	case _PC_REC_XFER_ALIGN:
		*retval = 4096;	/* XXX recommend page aligned buffers */
		break;
	case _PC_SYMLINK_MAX:
		*retval = 255;	/* Minimum acceptable POSIX value */
		break;
	case _PC_SYNC_IO:	/* unistd.h: _POSIX_SYNCHRONIZED_IO */
		*retval = 0;	/* [SIO] option is not supported */
		break;
	case _PC_XATTR_SIZE_BITS:
		/* The number of bits used to store maximum extended 
		 * attribute size in bytes.  For example, if the maximum 
		 * attribute size supported by a file system is 128K, the 
		 * value returned will be 18.  However a value 18 can mean 
		 * that the maximum attribute size can be anywhere from 
		 * (256KB - 1) to 128KB.  As a special case, the resource 
		 * fork can have much larger size, and some file system 
		 * specific extended attributes can have smaller and preset 
		 * size; for example, Finder Info is always 32 bytes.
		 */
		memset(&vfa, 0, sizeof(vfa));
		VFSATTR_INIT(&vfa);
		VFSATTR_WANTED(&vfa, f_capabilities);
		if (vfs_getattr(vnode_mount(vp), &vfa, ctx) == 0 &&
		    (VFSATTR_IS_SUPPORTED(&vfa, f_capabilities)) && 
		    (vfa.f_capabilities.capabilities[VOL_CAPABILITIES_INTERFACES] & VOL_CAP_INT_EXTENDED_ATTR) && 
		    (vfa.f_capabilities.valid[VOL_CAPABILITIES_INTERFACES] & VOL_CAP_INT_EXTENDED_ATTR)) {
			/* Supports native extended attributes */
			error = VNOP_PATHCONF(vp, name, retval, ctx);
		} else {
			/* Number of bits used to represent the maximum size of 
			 * extended attribute stored in an Apple Double file.
			 */
			*retval = AD_XATTR_SIZE_BITS;
		}
		break;
	default:
		error = VNOP_PATHCONF(vp, name, retval, ctx);
		break;
	}

	return (error);
}