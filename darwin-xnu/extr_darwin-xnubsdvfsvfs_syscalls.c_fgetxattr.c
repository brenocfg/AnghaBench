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
typedef  scalar_t__ user_ssize_t ;
typedef  int /*<<< orphan*/ * uio_t ;
typedef  int /*<<< orphan*/  uio_buf ;
struct fgetxattr_args {int options; scalar_t__ size; int /*<<< orphan*/  fd; int /*<<< orphan*/  value; int /*<<< orphan*/  position; int /*<<< orphan*/  attrname; } ;
typedef  int /*<<< orphan*/  proc_t ;
typedef  int /*<<< orphan*/  attrname ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 scalar_t__ IS_64BIT_PROCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UIO_READ ; 
 int UIO_SIZEOF (int) ; 
 int UIO_USERSPACE32 ; 
 int UIO_USERSPACE64 ; 
 int /*<<< orphan*/  XATTR_MAXNAMELEN ; 
 int XATTR_NODEFAULT ; 
 int XATTR_NOFOLLOW ; 
 int XATTR_NOSECURITY ; 
 int copyinstr (int /*<<< orphan*/ ,char*,int,size_t*) ; 
 int /*<<< orphan*/  file_drop (int /*<<< orphan*/ ) ; 
 int file_vnode (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uio_addiov (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * uio_createwithbuffer (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ uio_resid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfs_context_current () ; 
 int vn_getxattr (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,size_t*,int,int /*<<< orphan*/ ) ; 
 int vnode_getwithref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_put (int /*<<< orphan*/ ) ; 
 scalar_t__ xattr_protected (char*) ; 

int
fgetxattr(proc_t p, struct fgetxattr_args *uap, user_ssize_t *retval)
{
	vnode_t vp;
	char attrname[XATTR_MAXNAMELEN+1];
	uio_t auio = NULL;
	int spacetype = IS_64BIT_PROCESS(p) ? UIO_USERSPACE64 : UIO_USERSPACE32;
	size_t attrsize = 0;
	size_t namelen;
	int error;
	char uio_buf[ UIO_SIZEOF(1) ];

	if (uap->options & (XATTR_NOFOLLOW | XATTR_NOSECURITY | XATTR_NODEFAULT))
		return (EINVAL);

	if ( (error = file_vnode(uap->fd, &vp)) ) {
		return (error);
	}
	if ( (error = vnode_getwithref(vp)) ) {
		file_drop(uap->fd);
		return(error);
	}
	error = copyinstr(uap->attrname, attrname, sizeof(attrname), &namelen);
	if (error != 0) {
		goto out;
	}
	if (xattr_protected(attrname)) {
		error = EPERM;
		goto out;
	}
	if (uap->value && uap->size > 0) {
		auio = uio_createwithbuffer(1, uap->position, spacetype, UIO_READ,
		                            &uio_buf[0], sizeof(uio_buf));
		uio_addiov(auio, uap->value, uap->size);
	}

	error = vn_getxattr(vp, attrname, auio, &attrsize, uap->options, vfs_context_current());
out:
	(void)vnode_put(vp);
	file_drop(uap->fd);

	if (auio) {
		*retval = uap->size - uio_resid(auio);
	} else {
		*retval = (user_ssize_t)attrsize;
	}
	return (error);
}