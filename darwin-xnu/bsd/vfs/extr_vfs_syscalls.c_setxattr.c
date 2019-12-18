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
typedef  int /*<<< orphan*/  vnode_t ;
typedef  int /*<<< orphan*/  vfs_context_t ;
typedef  int /*<<< orphan*/ * uio_t ;
typedef  int /*<<< orphan*/  uio_buf ;
typedef  int /*<<< orphan*/  u_int32_t ;
struct setxattr_args {int options; int /*<<< orphan*/  size; int /*<<< orphan*/  value; int /*<<< orphan*/  position; int /*<<< orphan*/  path; int /*<<< orphan*/  attrname; } ;
struct nameidata {int /*<<< orphan*/  ni_vp; } ;
typedef  int /*<<< orphan*/  proc_t ;
typedef  int /*<<< orphan*/  attrname ;

/* Variables and functions */
 int EINVAL ; 
 int ENAMETOOLONG ; 
 int EPERM ; 
 int /*<<< orphan*/  FOLLOW ; 
 int /*<<< orphan*/  FSE_ARG_DONE ; 
 int /*<<< orphan*/  FSE_ARG_VNODE ; 
 int /*<<< orphan*/  FSE_XATTR_MODIFIED ; 
 scalar_t__ IS_64BIT_PROCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOOKUP ; 
 int /*<<< orphan*/  NDINIT (struct nameidata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OP_SETXATTR ; 
 int UIO_SIZEOF (int) ; 
 int UIO_USERSPACE32 ; 
 int UIO_USERSPACE64 ; 
 int /*<<< orphan*/  UIO_WRITE ; 
 int /*<<< orphan*/  XATTR_MAXNAMELEN ; 
 int XATTR_NODEFAULT ; 
 int XATTR_NOFOLLOW ; 
 int XATTR_NOSECURITY ; 
 int /*<<< orphan*/  add_fsevent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int copyinstr (int /*<<< orphan*/ ,char*,int,size_t*) ; 
 int namei (struct nameidata*) ; 
 int /*<<< orphan*/  nameidone (struct nameidata*) ; 
 int /*<<< orphan*/  uio_addiov (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * uio_createwithbuffer (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  vfs_context_current () ; 
 int vn_setxattr (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_put (int /*<<< orphan*/ ) ; 
 scalar_t__ xattr_protected (char*) ; 

int
setxattr(proc_t p, struct setxattr_args *uap, int *retval)
{
	vnode_t vp;
	struct nameidata nd;
	char attrname[XATTR_MAXNAMELEN+1];
	vfs_context_t ctx = vfs_context_current();
	uio_t auio = NULL;
	int spacetype = IS_64BIT_PROCESS(p) ? UIO_USERSPACE64 : UIO_USERSPACE32;
	size_t namelen;
	u_int32_t nameiflags;
	int error;
	char uio_buf[ UIO_SIZEOF(1) ];

	if (uap->options & (XATTR_NOSECURITY | XATTR_NODEFAULT))
		return (EINVAL);

	error = copyinstr(uap->attrname, attrname, sizeof(attrname), &namelen);
	if (error != 0) {
		if (error == EPERM) {
			/* if the string won't fit in attrname, copyinstr emits EPERM */
			return (ENAMETOOLONG);
		}
		/* Otherwise return the default error from copyinstr to detect ERANGE, etc */
		return error;
	}
	if (xattr_protected(attrname))
		return(EPERM);
	if (uap->size != 0 && uap->value == 0) {
		return (EINVAL);
	}

	nameiflags = (uap->options & XATTR_NOFOLLOW) ? 0 : FOLLOW;
	NDINIT(&nd, LOOKUP, OP_SETXATTR, nameiflags, spacetype, uap->path, ctx);
	if ((error = namei(&nd))) {
		return (error);
	}
	vp = nd.ni_vp;
	nameidone(&nd);

	auio = uio_createwithbuffer(1, uap->position, spacetype, UIO_WRITE,
	                            &uio_buf[0], sizeof(uio_buf));
	uio_addiov(auio, uap->value, uap->size);

	error = vn_setxattr(vp, attrname, auio, uap->options, ctx);
#if CONFIG_FSE
	if (error == 0) {
		add_fsevent(FSE_XATTR_MODIFIED, ctx,
		    FSE_ARG_VNODE, vp,
		    FSE_ARG_DONE);
	}
#endif
	vnode_put(vp);
	*retval = 0;
	return (error);
}