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
struct knote {int /*<<< orphan*/  kn_sdata; int /*<<< orphan*/  kn_sfflags; struct tty* kn_hook; } ;
struct kevent_internal_s {int /*<<< orphan*/  data; int /*<<< orphan*/  fflags; } ;

/* Variables and functions */
 int ptsd_kqops_common (struct knote*,struct tty*) ; 
 int /*<<< orphan*/  tty_lock (struct tty*) ; 
 int /*<<< orphan*/  tty_unlock (struct tty*) ; 

__attribute__((used)) static int
ptsd_kqops_touch(struct knote *kn, struct kevent_internal_s *kev)
{
	struct tty *tp;
	int ret;

	tp = kn->kn_hook;

	tty_lock(tp);

	/* accept new kevent state */
	kn->kn_sfflags = kev->fflags;
	kn->kn_sdata = kev->data;

	/* recapture fired state of knote */
	ret = ptsd_kqops_common(kn, tp);

	tty_unlock(tp);

	return ret;
}