#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* vnode_t ;
typedef  int /*<<< orphan*/  vfs_context_t ;
struct componentname {TYPE_1__* cn_ndp; } ;
typedef  int /*<<< orphan*/  kauth_action_t ;
struct TYPE_13__ {scalar_t__ v_type; scalar_t__ v_tag; } ;
struct TYPE_12__ {int ni_flag; } ;

/* Variables and functions */
 int EACCES ; 
 int EISDIR ; 
 int ELOOP ; 
 int ENOTDIR ; 
 int EOPNOTSUPP ; 
 int FREAD ; 
 int FWRITE ; 
 int /*<<< orphan*/  KAUTH_VNODE_APPEND_DATA ; 
 int /*<<< orphan*/  KAUTH_VNODE_READ_DATA ; 
 int /*<<< orphan*/  KAUTH_VNODE_WRITE_DATA ; 
 int MNT_MULTILABEL ; 
 int NAMEI_TRAILINGSLASH ; 
 int O_APPEND ; 
 int O_DIRECTORY ; 
 int O_NOFOLLOW ; 
 int O_TRUNC ; 
 scalar_t__ VDIR ; 
 scalar_t__ VLNK ; 
 scalar_t__ VSOCK ; 
 scalar_t__ VT_FDESC ; 
 int mac_vnode_check_open (int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int vfs_flags (int /*<<< orphan*/ ) ; 
 int vnode_authorize (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vnode_isdir (TYPE_2__*) ; 
 scalar_t__ vnode_isnamedstream (TYPE_2__*) ; 
 scalar_t__ vnode_isshadow (TYPE_2__*) ; 
 int vnode_label (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_mount (TYPE_2__*) ; 
 int vnode_verifynamedstream (TYPE_2__*) ; 

int
vn_authorize_open_existing(vnode_t vp, struct componentname *cnp, int fmode, vfs_context_t ctx, void *reserved)
{
	/* Open of existing case */
	kauth_action_t action;
	int error = 0;
	if (cnp->cn_ndp == NULL) {
		panic("NULL ndp");
	}
	if (reserved != NULL) {
		panic("reserved not NULL.");
	}

#if CONFIG_MACF
	/* XXX may do duplicate work here, but ignore that for now (idempotent) */
	if (vfs_flags(vnode_mount(vp)) & MNT_MULTILABEL) {
		error = vnode_label(vnode_mount(vp), NULL, vp, NULL, 0, ctx);
		if (error)
			return (error);
	}
#endif

	if ( (fmode & O_DIRECTORY) && vp->v_type != VDIR ) {
		return (ENOTDIR);
	}

	if (vp->v_type == VSOCK && vp->v_tag != VT_FDESC) {
		return (EOPNOTSUPP);	/* Operation not supported on socket */
	}

	if (vp->v_type == VLNK && (fmode & O_NOFOLLOW) != 0) {
		return (ELOOP);		/* O_NOFOLLOW was specified and the target is a symbolic link */
	}

	/* disallow write operations on directories */
	if (vnode_isdir(vp) && (fmode & (FWRITE | O_TRUNC))) {
		return (EISDIR);
	}

	if ((cnp->cn_ndp->ni_flag & NAMEI_TRAILINGSLASH)) {
		if (vp->v_type != VDIR) {
			return (ENOTDIR);
		}
	}

#if CONFIG_MACF
	/* If a file being opened is a shadow file containing 
	 * namedstream data, ignore the macf checks because it 
	 * is a kernel internal file and access should always 
	 * be allowed.
	 */
	if (!(vnode_isshadow(vp) && vnode_isnamedstream(vp))) {
		error = mac_vnode_check_open(ctx, vp, fmode);
		if (error) {
			return (error);
		}
	}
#endif

	/* compute action to be authorized */
	action = 0;
	if (fmode & FREAD) {
		action |= KAUTH_VNODE_READ_DATA;
	}
	if (fmode & (FWRITE | O_TRUNC)) {
		/*
		 * If we are writing, appending, and not truncating,
		 * indicate that we are appending so that if the
		 * UF_APPEND or SF_APPEND bits are set, we do not deny
		 * the open.
		 */
		if ((fmode & O_APPEND) && !(fmode & O_TRUNC)) {
			action |= KAUTH_VNODE_APPEND_DATA;
		} else {
			action |= KAUTH_VNODE_WRITE_DATA;
		}
	}
	error = vnode_authorize(vp, NULL, action, ctx);
#if NAMEDSTREAMS
	if (error == EACCES) {
		/*
		 * Shadow files may exist on-disk with a different UID/GID
		 * than that of the current context.  Verify that this file
		 * is really a shadow file.  If it was created successfully
		 * then it should be authorized.
		 */
		if (vnode_isshadow(vp) && vnode_isnamedstream (vp)) {
			error = vnode_verifynamedstream(vp);
		}
	}
#endif

	return error;
}