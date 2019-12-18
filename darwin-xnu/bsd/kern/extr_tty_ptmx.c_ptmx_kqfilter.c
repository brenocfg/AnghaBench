#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tty {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  si_note; } ;
struct TYPE_4__ {int /*<<< orphan*/  si_note; } ;
struct ptmx_ioctl {TYPE_2__ pt_selw; TYPE_1__ pt_selr; struct tty* pt_tty; } ;
struct knote {int kn_filter; struct ptmx_ioctl* kn_hook; int /*<<< orphan*/  kn_filtid; } ;
typedef  int /*<<< orphan*/  dev_t ;
struct TYPE_6__ {scalar_t__ d_open; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  EVFILTID_PTMX ; 
#define  EVFILT_READ 129 
#define  EVFILT_WRITE 128 
 int /*<<< orphan*/  KNOTE_ATTACH (int /*<<< orphan*/ *,struct knote*) ; 
 TYPE_3__* cdevsw ; 
 int /*<<< orphan*/  knote_set_error (struct knote*,int /*<<< orphan*/ ) ; 
 size_t major (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  minor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,int,struct knote*,struct tty*) ; 
 scalar_t__ ptcopen ; 
 struct ptmx_ioctl* ptmx_get_ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ptmx_kqops_common (struct knote*,struct ptmx_ioctl*,struct tty*) ; 
 int /*<<< orphan*/  tty_lock (struct tty*) ; 
 int /*<<< orphan*/  tty_unlock (struct tty*) ; 
 int /*<<< orphan*/  ttyhold (struct tty*) ; 

int
ptmx_kqfilter(dev_t dev, struct knote *kn)
{
	struct tty *tp = NULL;
	struct ptmx_ioctl *pti = NULL;
	int ret;

	/* make sure we're talking about the right device type */
	if (cdevsw[major(dev)].d_open != ptcopen) {
		knote_set_error(kn, ENODEV);
		return 0;
	}

	if ((pti = ptmx_get_ioctl(minor(dev), 0)) == NULL) {
		knote_set_error(kn, ENXIO);
		return 0;
	}

	tp = pti->pt_tty;
	tty_lock(tp);

	kn->kn_filtid = EVFILTID_PTMX;
	kn->kn_hook = pti;

	/*
	 * Attach to the ptmx's selinfo structures.  This is the major difference
	 * to the ptsd filtops, which use the selinfo structures in the tty
	 * structure.
	 */
	switch (kn->kn_filter) {
	case EVFILT_READ:
		KNOTE_ATTACH(&pti->pt_selr.si_note, kn);
		break;
	case EVFILT_WRITE:
		KNOTE_ATTACH(&pti->pt_selw.si_note, kn);
		break;
	default:
		panic("ptmx kevent: unexpected filter: %d, kn = %p, tty = %p",
				kn->kn_filter, kn, tp);
		break;
	}

	/* capture current event state */
	ret = ptmx_kqops_common(kn, pti, tp);

	/* take a reference on the TTY */
	ttyhold(tp);
	tty_unlock(tp);

	return ret;
}