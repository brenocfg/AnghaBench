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
typedef  scalar_t__ vnode_t ;
typedef  int /*<<< orphan*/  vfs_context_t ;
typedef  int /*<<< orphan*/  uthread_t ;
struct kevent_internal_s {int dummy; } ;
struct knote {int kn_flags; int kn_sfflags; int kn_data; int kn_sdata; scalar_t__ kn_fflags; struct kevent_internal_s kn_kevent; int /*<<< orphan*/  kn_hookid; TYPE_2__* kn_fp; } ;
struct filt_process_s {int dummy; } ;
struct TYPE_4__ {TYPE_1__* f_fglob; } ;
struct TYPE_3__ {scalar_t__ fg_data; } ;

/* Variables and functions */
 int EV_CLEAR ; 
 int EV_EOF ; 
 int EV_ONESHOT ; 
 int NOTE_LOWAT ; 
 int /*<<< orphan*/  current_thread () ; 
 int /*<<< orphan*/  filt_spec_common (struct knote*,int) ; 
 int /*<<< orphan*/  get_bsdthread_info (int /*<<< orphan*/ ) ; 
 int spec_knote_select_and_link (struct knote*) ; 
 int /*<<< orphan*/  vfs_context_current () ; 
 int vnode_getwithvid (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_put (scalar_t__) ; 

__attribute__((used)) static int
filt_specprocess(struct knote *kn, struct filt_process_s *data, struct kevent_internal_s *kev)
{
#pragma unused(data)
	vnode_t vp;
	uthread_t uth;
	vfs_context_t ctx;
	int res;
	int selres;
	int error;

	uth = get_bsdthread_info(current_thread());
	ctx = vfs_context_current();
	vp = (vnode_t)kn->kn_fp->f_fglob->fg_data;

	error = vnode_getwithvid(vp, kn->kn_hookid);
	if (error != 0) {
		kn->kn_flags |= (EV_EOF | EV_ONESHOT);
		*kev = kn->kn_kevent;
		return 1;
	}

	selres = spec_knote_select_and_link(kn);
	filt_spec_common(kn, selres);

	vnode_put(vp);

	res = ((kn->kn_sfflags & NOTE_LOWAT) != 0) ?
		(kn->kn_data >= kn->kn_sdata) : kn->kn_data;

	if (res) {
		*kev = kn->kn_kevent;
		if (kn->kn_flags & EV_CLEAR) {
			kn->kn_fflags = 0;
			kn->kn_data = 0;
		}
	}

	return res;
}