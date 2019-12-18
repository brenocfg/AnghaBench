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
struct tty {int dummy; } ;
struct ptmx_ioctl {int dummy; } ;
struct knote {int /*<<< orphan*/  kn_sdata; int /*<<< orphan*/  kn_sfflags; } ;
struct kevent_internal_s {int /*<<< orphan*/  data; int /*<<< orphan*/  fflags; } ;

/* Variables and functions */
 struct ptmx_ioctl* ptmx_knote_ioctl (struct knote*) ; 
 struct tty* ptmx_knote_tty (struct knote*) ; 
 int ptmx_kqops_common (struct knote*,struct ptmx_ioctl*,struct tty*) ; 
 int /*<<< orphan*/  tty_lock (struct tty*) ; 
 int /*<<< orphan*/  tty_unlock (struct tty*) ; 

__attribute__((used)) static int
ptmx_kqops_touch(struct knote *kn, struct kevent_internal_s *kev)
{
	struct ptmx_ioctl *pti = ptmx_knote_ioctl(kn);
	struct tty *tp = ptmx_knote_tty(kn);
	int ret;

	tty_lock(tp);

	/* accept new kevent state */
	kn->kn_sfflags = kev->fflags;
	kn->kn_sdata = kev->data;

	/* recapture fired state of knote */
	ret = ptmx_kqops_common(kn, pti, tp);

	tty_unlock(tp);

	return ret;
}