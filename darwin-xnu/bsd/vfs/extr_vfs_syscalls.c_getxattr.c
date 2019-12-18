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
typedef  size_t user_ssize_t ;
typedef  int /*<<< orphan*/ * uio_t ;
typedef  int /*<<< orphan*/  uio_buf ;
typedef  int /*<<< orphan*/  u_int32_t ;
struct nameidata {int /*<<< orphan*/  ni_vp; } ;
struct getxattr_args {int options; int size; int /*<<< orphan*/  value; int /*<<< orphan*/  position; int /*<<< orphan*/  attrname; int /*<<< orphan*/  path; } ;
typedef  int /*<<< orphan*/  proc_t ;
typedef  int /*<<< orphan*/  attrname ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  FOLLOW ; 
 scalar_t__ IS_64BIT_PROCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOOKUP ; 
 int /*<<< orphan*/  NDINIT (struct nameidata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OP_GETXATTR ; 
 int /*<<< orphan*/  UIO_READ ; 
 int UIO_SIZEOF (int) ; 
 int UIO_USERSPACE32 ; 
 int UIO_USERSPACE64 ; 
 int /*<<< orphan*/  XATTR_MAXNAMELEN ; 
 size_t XATTR_MAXSIZE ; 
 int XATTR_NODEFAULT ; 
 int XATTR_NOFOLLOW ; 
 int XATTR_NOSECURITY ; 
 int copyinstr (int /*<<< orphan*/ ,char*,int,size_t*) ; 
 int namei (struct nameidata*) ; 
 int /*<<< orphan*/  nameidone (struct nameidata*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  uio_addiov (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/ * uio_createwithbuffer (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,int) ; 
 size_t uio_resid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfs_context_current () ; 
 int /*<<< orphan*/  vfs_context_issuser (int /*<<< orphan*/ ) ; 
 int vn_getxattr (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,size_t*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_put (int /*<<< orphan*/ ) ; 
 scalar_t__ xattr_protected (char*) ; 

int
getxattr(proc_t p, struct getxattr_args *uap, user_ssize_t *retval)
{
	vnode_t vp;
	struct nameidata nd;
	char attrname[XATTR_MAXNAMELEN+1];
	vfs_context_t ctx = vfs_context_current();
	uio_t auio = NULL;
	int spacetype = IS_64BIT_PROCESS(p) ? UIO_USERSPACE64 : UIO_USERSPACE32;
	size_t attrsize = 0;
	size_t namelen;
	u_int32_t nameiflags;
	int error;
	char uio_buf[ UIO_SIZEOF(1) ];

	if (uap->options & (XATTR_NOSECURITY | XATTR_NODEFAULT))
		return (EINVAL);

	nameiflags = (uap->options & XATTR_NOFOLLOW) ? 0 : FOLLOW;
	NDINIT(&nd, LOOKUP, OP_GETXATTR, nameiflags, spacetype, uap->path, ctx);
	if ((error = namei(&nd))) {
		return (error);
	}
	vp = nd.ni_vp;
	nameidone(&nd);

	error = copyinstr(uap->attrname, attrname, sizeof(attrname), &namelen);
	if (error != 0) {
		goto out;
	}
	if (xattr_protected(attrname)) {
		if (!vfs_context_issuser(ctx) || strcmp(attrname, "com.apple.system.Security") != 0) {
			error = EPERM;
			goto out;
		}
	}
	/*
	 * the specific check for 0xffffffff is a hack to preserve
	 * binaray compatibilty in K64 with applications that discovered
	 * that passing in a buf pointer and a size of -1 resulted in
	 * just the size of the indicated extended attribute being returned.
	 * this isn't part of the documented behavior, but because of the
	 * original implemtation's check for "uap->size > 0", this behavior
	 * was allowed. In K32 that check turned into a signed comparison
	 * even though uap->size is unsigned...  in K64, we blow by that
	 * check because uap->size is unsigned and doesn't get sign smeared
	 * in the munger for a 32 bit user app.  we also need to add a
	 * check to limit the maximum size of the buffer being passed in...
	 * unfortunately, the underlying fileystems seem to just malloc
	 * the requested size even if the actual extended attribute is tiny.
	 * because that malloc is for kernel wired memory, we have to put a
	 * sane limit on it.
	 *
	 * U32 running on K64 will yield 0x00000000ffffffff for uap->size
	 * U64 running on K64 will yield -1 (64 bits wide)
	 * U32/U64 running on K32 will yield -1 (32 bits wide)
	 */
	if (uap->size == 0xffffffff || uap->size == (size_t)-1)
		goto no_uio;

	if (uap->value) {
		if (uap->size > (size_t)XATTR_MAXSIZE)
			uap->size = XATTR_MAXSIZE;

		auio = uio_createwithbuffer(1, uap->position, spacetype, UIO_READ,
		                            &uio_buf[0], sizeof(uio_buf));
		uio_addiov(auio, uap->value, uap->size);
	}
no_uio:
	error = vn_getxattr(vp, attrname, auio, &attrsize, uap->options, ctx);
out:
	vnode_put(vp);

	if (auio) {
		*retval = uap->size - uio_resid(auio);
	} else {
		*retval = (user_ssize_t)attrsize;
	}

	return (error);
}