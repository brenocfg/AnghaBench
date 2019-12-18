#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_9__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vnode_t ;
typedef  int /*<<< orphan*/  vfs_context_t ;
typedef  int /*<<< orphan*/  user_addr_t ;
struct vnode_attr {int /*<<< orphan*/  va_mode; } ;
struct TYPE_12__ {int /*<<< orphan*/  cn_hash; int /*<<< orphan*/  cn_namelen; int /*<<< orphan*/  cn_nameptr; int /*<<< orphan*/  cn_flags; } ;
struct nameidata {TYPE_9__ ni_cnd; TYPE_1__* ni_vp; TYPE_1__* ni_dvp; int /*<<< orphan*/  ni_flag; } ;
typedef  enum uio_seg { ____Placeholder_uio_seg } uio_seg ;
struct TYPE_11__ {scalar_t__ v_parent; int /*<<< orphan*/ * v_name; } ;

/* Variables and functions */
 int AUDITVNPATH1 ; 
 int /*<<< orphan*/  AUDIT_ARG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CREATE ; 
 int EACCES ; 
 int EEXIST ; 
 int EKEEPLOOKING ; 
 int EPERM ; 
 int /*<<< orphan*/  FSE_ARG_DONE ; 
 int /*<<< orphan*/  FSE_ARG_VNODE ; 
 int /*<<< orphan*/  FSE_CREATE_DIR ; 
 int LOCKPARENT ; 
 int /*<<< orphan*/  LOOKUP ; 
 int /*<<< orphan*/  NAMEI_COMPOUNDMKDIR ; 
 int /*<<< orphan*/  NDINIT (struct nameidata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ NULLVP ; 
 int /*<<< orphan*/  OP_MKDIR ; 
 int /*<<< orphan*/  VATTR_SET (struct vnode_attr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VDIR ; 
 int VNODE_UPDATE_NAME ; 
 int VNODE_UPDATE_PARENT ; 
 int /*<<< orphan*/  WILLBEDIR ; 
 int /*<<< orphan*/  add_fsevent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mode ; 
 int nameiat (struct nameidata*,int) ; 
 int /*<<< orphan*/  nameidone (struct nameidata*) ; 
 int /*<<< orphan*/  va_type ; 
 int vn_authorize_mkdir (TYPE_1__*,TYPE_9__*,struct vnode_attr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int vn_create (TYPE_1__*,TYPE_1__**,struct nameidata*,struct vnode_attr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int vnode_compound_mkdir_available (TYPE_1__*) ; 
 int /*<<< orphan*/  vnode_put (TYPE_1__*) ; 
 int /*<<< orphan*/  vnode_update_identity (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
mkdir1at(vfs_context_t ctx, user_addr_t path, struct vnode_attr *vap, int fd,
    enum uio_seg segflg)
{
	vnode_t	vp, dvp;
	int error;
	int update_flags = 0;
	int batched;
	struct nameidata nd;

	AUDIT_ARG(mode, vap->va_mode);
	NDINIT(&nd, CREATE, OP_MKDIR, LOCKPARENT | AUDITVNPATH1, segflg,
	       path, ctx);
	nd.ni_cnd.cn_flags |= WILLBEDIR;
	nd.ni_flag = NAMEI_COMPOUNDMKDIR;

continue_lookup:
	error = nameiat(&nd, fd);
	if (error)
		return (error);
	dvp = nd.ni_dvp;
	vp = nd.ni_vp;

	if (vp != NULL) {
		error = EEXIST;
		goto out;
	}

	batched = vnode_compound_mkdir_available(dvp);

	VATTR_SET(vap, va_type, VDIR);

	/*
	 * XXX
	 * Don't authorize in VFS for compound VNOP.... mkdir -p today assumes that it will
	 * only get EXISTS or EISDIR for existing path components, and not that it could see
	 * EACCESS/EPERM--so if we authorize for mkdir on "/" for "mkdir -p /tmp/foo/bar/baz"
	 * it will fail in a spurious  manner.  Need to figure out if this is valid behavior.
	 */
	if ((error = vn_authorize_mkdir(dvp, &nd.ni_cnd, vap, ctx, NULL)) != 0) {
		if (error == EACCES || error == EPERM) {
			int error2;

			nameidone(&nd);
			vnode_put(dvp);
			dvp = NULLVP;

			/*
			 * Try a lookup without "NAMEI_COMPOUNDVNOP" to make sure we return EEXIST
			 * rather than EACCESS if the target exists.
			 */
			NDINIT(&nd, LOOKUP, OP_MKDIR, AUDITVNPATH1, segflg,
				       	path, ctx);
			error2 = nameiat(&nd, fd);
			if (error2) {
				goto out;
			} else {
				vp = nd.ni_vp;
				error = EEXIST;
				goto out;
			}
		}

		goto out;
	}

	/*
	 * make the directory
	 */
	if ((error = vn_create(dvp, &vp, &nd, vap, 0, 0, NULL, ctx)) != 0) {
		if (error == EKEEPLOOKING) {
			nd.ni_vp = vp;
			goto continue_lookup;
		}

		goto out;
	}

	// Make sure the name & parent pointers are hooked up
	if (vp->v_name == NULL)
	        update_flags |= VNODE_UPDATE_NAME;
	if (vp->v_parent == NULLVP)
	        update_flags |= VNODE_UPDATE_PARENT;

	if (update_flags)
	        vnode_update_identity(vp, dvp, nd.ni_cnd.cn_nameptr, nd.ni_cnd.cn_namelen, nd.ni_cnd.cn_hash, update_flags);

#if CONFIG_FSE
	add_fsevent(FSE_CREATE_DIR, ctx, FSE_ARG_VNODE, vp, FSE_ARG_DONE);
#endif

out:
	/*
	 * nameidone has to happen before we vnode_put(dvp)
	 * since it may need to release the fs_nodelock on the dvp
	 */
	nameidone(&nd);

	if (vp)
		vnode_put(vp);
	if (dvp)
		vnode_put(dvp);

	return (error);
}