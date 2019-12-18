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
struct vnode {int v_flag; scalar_t__ v_parent; scalar_t__ v_tag; int v_writecount; } ;

/* Variables and functions */
 int /*<<< orphan*/  FSE_ARG_DONE ; 
 int /*<<< orphan*/  FSE_ARG_VNODE ; 
 int /*<<< orphan*/  FSE_CONTENT_MODIFIED ; 
 int FWASWRITTEN ; 
 int FWRITE ; 
 int /*<<< orphan*/  MNT_NOWAIT ; 
 scalar_t__ NULLVP ; 
 int VISNAMEDSTREAM ; 
 int VNOP_CLOSE (struct vnode*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VNOP_FSYNC (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ VT_HFS ; 
 int /*<<< orphan*/  add_fsevent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vnode*,int /*<<< orphan*/ ) ; 
 scalar_t__ need_fsevent (int /*<<< orphan*/ ,struct vnode*) ; 
 int vnode_flushnamedstream (scalar_t__,struct vnode*,int /*<<< orphan*/ ) ; 
 scalar_t__ vnode_isshadow (struct vnode*) ; 
 scalar_t__ vnode_isspec (struct vnode*) ; 
 int /*<<< orphan*/  vnode_rele_ext (struct vnode*,int,int /*<<< orphan*/ ) ; 

int
vn_close(struct vnode *vp, int flags, vfs_context_t ctx)
{
	int error;
	int flusherror = 0;

#if NAMEDRSRCFORK
	/* Sync data from resource fork shadow file if needed. */
	if ((vp->v_flag & VISNAMEDSTREAM) && 
	    (vp->v_parent != NULLVP) &&
	    vnode_isshadow(vp)) {
		if (flags & FWASWRITTEN) {
			flusherror = vnode_flushnamedstream(vp->v_parent, vp, ctx);
		}
	}
#endif
	
	/* work around for foxhound */
	if (vnode_isspec(vp))
		(void)vnode_rele_ext(vp, flags, 0);

	/*
	 * On HFS, we flush when the last writer closes.  We do this
	 * because resource fork vnodes hold a reference on data fork
	 * vnodes and that will prevent them from getting VNOP_INACTIVE
	 * which will delay when we flush cached data.  In future, we
	 * might find it beneficial to do this for all file systems.
	 * Note that it's OK to access v_writecount without the lock
	 * in this context.
	 */
	if (vp->v_tag == VT_HFS && (flags & FWRITE) && vp->v_writecount == 1)
		VNOP_FSYNC(vp, MNT_NOWAIT, ctx);

	error = VNOP_CLOSE(vp, flags, ctx);

#if CONFIG_FSE
	if (flags & FWASWRITTEN) {
	        if (need_fsevent(FSE_CONTENT_MODIFIED, vp)) {
		        add_fsevent(FSE_CONTENT_MODIFIED, ctx,
				    FSE_ARG_VNODE, vp,
				    FSE_ARG_DONE);
		}
	}
#endif

	if (!vnode_isspec(vp))
		(void)vnode_rele_ext(vp, flags, 0);
	
	if (flusherror) {
		error = flusherror;
	}
	return (error);
}