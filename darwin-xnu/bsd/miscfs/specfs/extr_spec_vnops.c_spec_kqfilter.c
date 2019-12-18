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
typedef  int /*<<< orphan*/  vnode_t ;
struct knote {int kn_flags; int kn_vnode_kqok; int kn_vnode_use_ofst; int /*<<< orphan*/  kn_filtid; int /*<<< orphan*/  kn_data; } ;
struct kevent_internal_s {int dummy; } ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  dev_t ;
struct TYPE_4__ {scalar_t__ d_type; } ;
struct TYPE_3__ {int (* f_attach ) (struct knote*,struct kevent_internal_s*) ;} ;

/* Variables and functions */
 int CDEVSW_IS_PTC ; 
 int CDEVSW_IS_PTS ; 
 int CDEVSW_SELECT_KQUEUE ; 
 int CDEVSW_USE_OFFSET ; 
 scalar_t__ D_TTY ; 
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  EVFILTID_PTMX ; 
 int /*<<< orphan*/  EVFILTID_PTSD ; 
 int /*<<< orphan*/  EVFILTID_TTY ; 
 int EV_ERROR ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int bpfkqfilter (int /*<<< orphan*/ ,struct knote*) ; 
 TYPE_2__* cdevsw ; 
 int* cdevsw_flags ; 
 int filt_specattach (struct knote*,struct kevent_internal_s*) ; 
 TYPE_1__* knote_fops (struct knote*) ; 
 int /*<<< orphan*/  knote_set_error (struct knote*,int /*<<< orphan*/ ) ; 
 size_t major (int /*<<< orphan*/ ) ; 
 size_t nchrdev ; 
 int ptmx_kqfilter (int /*<<< orphan*/ ,struct knote*) ; 
 int ptsd_kqfilter (int /*<<< orphan*/ ,struct knote*) ; 
 int stub1 (struct knote*,struct kevent_internal_s*) ; 
 int /*<<< orphan*/  vnode_ischr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_specrdev (int /*<<< orphan*/ ) ; 

int
spec_kqfilter(vnode_t vp, struct knote *kn, struct kevent_internal_s *kev)
{
	dev_t dev;

	assert(vnode_ischr(vp));

	dev = vnode_specrdev(vp);

#if NETWORKING
	/*
	 * Try a bpf device, as defined in bsd/net/bpf.c
	 * If it doesn't error out the attach, then it
	 * claimed it. Otherwise, fall through and try
	 * other attaches.
	 */
	int32_t tmp_flags = kn->kn_flags;
	int64_t tmp_data = kn->kn_data;
	int res;

	res = bpfkqfilter(dev, kn);
	if ((kn->kn_flags & EV_ERROR) == 0) {
		return res;
	}
	kn->kn_flags = tmp_flags;
	kn->kn_data = tmp_data;
#endif

	if (major(dev) > nchrdev) {
		knote_set_error(kn, ENXIO);
		return 0;
	}

	kn->kn_vnode_kqok = !!(cdevsw_flags[major(dev)] & CDEVSW_SELECT_KQUEUE);
	kn->kn_vnode_use_ofst = !!(cdevsw_flags[major(dev)] & CDEVSW_USE_OFFSET);

	if (cdevsw_flags[major(dev)] & CDEVSW_IS_PTS) {
		kn->kn_filtid = EVFILTID_PTSD;
		return ptsd_kqfilter(dev, kn);
	} else if (cdevsw_flags[major(dev)] & CDEVSW_IS_PTC) {
		kn->kn_filtid = EVFILTID_PTMX;
		return ptmx_kqfilter(dev, kn);
	} else if (cdevsw[major(dev)].d_type == D_TTY && kn->kn_vnode_kqok) {
		/*
		 * TTYs from drivers that use struct ttys use their own filter
		 * routines.  The PTC driver doesn't use the tty for character
		 * counts, so it must go through the select fallback.
		 */
		kn->kn_filtid = EVFILTID_TTY;
		return knote_fops(kn)->f_attach(kn, kev);
	}

	/* Try to attach to other char special devices */
	return filt_specattach(kn, kev);
}