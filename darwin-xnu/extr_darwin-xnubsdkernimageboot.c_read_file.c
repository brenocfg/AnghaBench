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
typedef  int /*<<< orphan*/  vfs_context_t ;
struct vnode {int dummy; } ;
struct nameidata {struct vnode* ni_vp; } ;
typedef  int /*<<< orphan*/  proc_t ;
typedef  size_t off_t ;
typedef  int /*<<< orphan*/  kauth_cred_t ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUTHPRNT (char*,...) ; 
 int /*<<< orphan*/  CAST_USER_ADDR_T (char const*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FREAD ; 
 int /*<<< orphan*/  IO_NODELOCKED ; 
 int /*<<< orphan*/  LOCKLEAF ; 
 int /*<<< orphan*/  LOOKUP ; 
 int /*<<< orphan*/  NDINIT (struct nameidata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OP_OPEN ; 
 int /*<<< orphan*/  UIO_READ ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int /*<<< orphan*/  VNOP_CLOSE (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int VNOP_OPEN (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* kalloc (size_t) ; 
 int /*<<< orphan*/  kfree_safe (char*) ; 
 int namei (struct nameidata*) ; 
 int /*<<< orphan*/  nameidone (struct nameidata*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  vfs_context_kernel () ; 
 int /*<<< orphan*/  vfs_context_proc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_context_ucred (int /*<<< orphan*/ ) ; 
 int vn_rdwr (int /*<<< orphan*/ ,struct vnode*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_put (struct vnode*) ; 
 int vnode_size (struct vnode*,size_t*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
read_file(const char *path, void **bufp, size_t *bufszp)
{
	int err = 0;
	struct nameidata ndp = {};
	struct vnode *vp = NULL;
	off_t fsize = 0;
	int resid = 0;
	char *buf = NULL;
	bool doclose = false;

	vfs_context_t ctx = vfs_context_kernel();
	proc_t p = vfs_context_proc(ctx);
	kauth_cred_t kerncred = vfs_context_ucred(ctx);

	NDINIT(&ndp, LOOKUP, OP_OPEN, LOCKLEAF, UIO_SYSSPACE, CAST_USER_ADDR_T(path), ctx);
	if ((err = namei(&ndp)) != 0) {
		AUTHPRNT("namei failed (%s)", path);
		goto out;
	}
	nameidone(&ndp);
	vp = ndp.ni_vp;

	if ((err = vnode_size(vp, &fsize, ctx)) != 0) {
		AUTHPRNT("failed to get vnode size");
		goto out;
	}
	if (fsize < 0) {
		panic("negative file size");
	}

	if ((err = VNOP_OPEN(vp, FREAD, ctx)) != 0) {
		AUTHPRNT("failed to open vnode");
		goto out;
	}
	doclose = true;

	/* if bufsz is non-zero, cap the read at bufsz bytes */
	if (*bufszp && *bufszp < (size_t)fsize) {
		fsize = *bufszp;
	}

	buf = kalloc(fsize);
	if (buf == NULL) {
		err = ENOMEM;
		goto out;
	}

	if ((err = vn_rdwr(UIO_READ, vp, (caddr_t)buf, fsize, 0, UIO_SYSSPACE, IO_NODELOCKED, kerncred, &resid, p)) != 0) {
		AUTHPRNT("vn_rdwr() failed");
		goto out;
	}

	if (resid) {
		/* didnt get everything we wanted */
		AUTHPRNT("vn_rdwr resid = %d", resid);
		err = EINVAL;
		goto out;
	}

out:
	if (doclose) {
		VNOP_CLOSE(vp, FREAD, ctx);
	}
	if (vp) {
		vnode_put(vp);
		vp = NULL;
	}

	if (err) {
		kfree_safe(buf);
	} else {
		*bufp = buf;
		*bufszp = fsize;
	}

	return err;
}