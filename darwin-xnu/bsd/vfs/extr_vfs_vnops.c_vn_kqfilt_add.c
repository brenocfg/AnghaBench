#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vfs_context_t ;
struct vnode {int /*<<< orphan*/  v_knotes; TYPE_1__* v_fifoinfo; } ;
struct knote {int kn_filter; int kn_flags; int kn_data; int /*<<< orphan*/  kn_filtid; int /*<<< orphan*/  kn_hookid; void* kn_hook; } ;
struct kevent_internal_s {int dummy; } ;
struct fileproc {TYPE_2__* f_fglob; } ;
struct TYPE_4__ {int /*<<< orphan*/  fg_cred; scalar_t__ fg_data; } ;
struct TYPE_3__ {int /*<<< orphan*/  fi_readsock; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTSUP ; 
 int /*<<< orphan*/  EVFILTID_VN ; 
#define  EVFILT_READ 130 
#define  EVFILT_VNODE 129 
#define  EVFILT_WRITE 128 
 int EV_ERROR ; 
 int /*<<< orphan*/  KNOTE_ATTACH (int /*<<< orphan*/ *,struct knote*) ; 
 int /*<<< orphan*/  VNODE_MONITOR_BEGIN ; 
 int /*<<< orphan*/  VNODE_NODEAD ; 
 int /*<<< orphan*/  VNOP_MONITOR (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int filt_vnode_common (struct knote*,struct vnode*,int /*<<< orphan*/ ) ; 
 int mac_vnode_check_kqfilter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct knote*,struct vnode*) ; 
 int spec_kqfilter (struct vnode*,struct knote*,struct kevent_internal_s*) ; 
 int vget_internal (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_ischr (struct vnode*) ; 
 int /*<<< orphan*/  vnode_isfifo (struct vnode*) ; 
 int /*<<< orphan*/  vnode_isreg (struct vnode*) ; 
 int /*<<< orphan*/  vnode_lock (struct vnode*) ; 
 int /*<<< orphan*/  vnode_put (struct vnode*) ; 
 int /*<<< orphan*/  vnode_unlock (struct vnode*) ; 
 int /*<<< orphan*/  vnode_vid (struct vnode*) ; 

__attribute__((used)) static int
vn_kqfilt_add(struct fileproc *fp, struct knote *kn,
		struct kevent_internal_s *kev, vfs_context_t ctx)
{
	struct vnode *vp;
	int error = 0;
	int result = 0;

	vp = (struct vnode *)fp->f_fglob->fg_data;

	/*
	 * Don't attach a knote to a dead vnode.
	 */
	if ((error = vget_internal(vp, 0, VNODE_NODEAD)) == 0) {
		switch (kn->kn_filter) {
			case EVFILT_READ:
			case EVFILT_WRITE:
				if (vnode_isfifo(vp)) {
					/* We'll only watch FIFOs that use our fifofs */
					if (!(vp->v_fifoinfo && vp->v_fifoinfo->fi_readsock)) {
						error = ENOTSUP;
					}

				} else if (!vnode_isreg(vp)) {
					if (vnode_ischr(vp)) {
						result = spec_kqfilter(vp, kn, kev);
						if ((kn->kn_flags & EV_ERROR) == 0) {
							/* claimed by a special device */
							vnode_put(vp);
							return result;
						}
					}
					error = EINVAL;
				}
				break;
			case EVFILT_VNODE:
				break;
			default:
				error = EINVAL;
		}

		if (error == 0) {

#if CONFIG_MACF
			error = mac_vnode_check_kqfilter(ctx, fp->f_fglob->fg_cred, kn, vp);
			if (error) {
				vnode_put(vp);
				goto out;
			}
#endif

			kn->kn_hook = (void*)vp;
			kn->kn_hookid = vnode_vid(vp);
			kn->kn_filtid = EVFILTID_VN;

			vnode_lock(vp);
			KNOTE_ATTACH(&vp->v_knotes, kn);
			result = filt_vnode_common(kn, vp, 0);
			vnode_unlock(vp);

			/*
			 * Ask the filesystem to provide remove notifications,
			 * but ignore failure
			 */
			VNOP_MONITOR(vp, 0, VNODE_MONITOR_BEGIN, (void*) kn,  ctx);
		}

		vnode_put(vp);
	}

 out:
	if (error) {
		kn->kn_flags = EV_ERROR;
		kn->kn_data = error;
	}

	return result;
}