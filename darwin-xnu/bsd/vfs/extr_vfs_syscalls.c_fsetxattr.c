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
struct fsetxattr_args {int options; int /*<<< orphan*/  fd; int /*<<< orphan*/  size; int /*<<< orphan*/  value; int /*<<< orphan*/  position; int /*<<< orphan*/  attrname; } ;
typedef  int /*<<< orphan*/  proc_t ;
typedef  int /*<<< orphan*/  attrname ;

/* Variables and functions */
 int EINVAL ; 
 int ENAMETOOLONG ; 
 int EPERM ; 
 int /*<<< orphan*/  FSE_ARG_DONE ; 
 int /*<<< orphan*/  FSE_ARG_VNODE ; 
 int /*<<< orphan*/  FSE_XATTR_MODIFIED ; 
 scalar_t__ IS_64BIT_PROCESS (int /*<<< orphan*/ ) ; 
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
 int /*<<< orphan*/  file_drop (int /*<<< orphan*/ ) ; 
 int file_vnode (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uio_addiov (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * uio_createwithbuffer (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  vfs_context_current () ; 
 int vn_setxattr (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int vnode_getwithref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_put (int /*<<< orphan*/ ) ; 
 scalar_t__ xattr_protected (char*) ; 

int
fsetxattr(proc_t p, struct fsetxattr_args *uap, int *retval)
{
	vnode_t vp;
	char attrname[XATTR_MAXNAMELEN+1];
	uio_t auio = NULL;
	int spacetype = IS_64BIT_PROCESS(p) ? UIO_USERSPACE64 : UIO_USERSPACE32;
	size_t namelen;
	int error;
	char uio_buf[ UIO_SIZEOF(1) ];
#if CONFIG_FSE
	vfs_context_t ctx = vfs_context_current();
#endif

	if (uap->options & (XATTR_NOFOLLOW | XATTR_NOSECURITY | XATTR_NODEFAULT))
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
	if ( (error = file_vnode(uap->fd, &vp)) ) {
		return (error);
	}
	if ( (error = vnode_getwithref(vp)) ) {
		file_drop(uap->fd);
		return(error);
	}
	auio = uio_createwithbuffer(1, uap->position, spacetype, UIO_WRITE,
	                            &uio_buf[0], sizeof(uio_buf));
	uio_addiov(auio, uap->value, uap->size);

	error = vn_setxattr(vp, attrname, auio, uap->options, vfs_context_current());
#if CONFIG_FSE
	if (error == 0) {
		add_fsevent(FSE_XATTR_MODIFIED, ctx,
		    FSE_ARG_VNODE, vp,
		    FSE_ARG_DONE);
	}
#endif
	vnode_put(vp);
	file_drop(uap->fd);
	*retval = 0;
	return (error);
}