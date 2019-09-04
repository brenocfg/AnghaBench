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
struct knote {scalar_t__ kn_vnode_kqok; int /*<<< orphan*/  kn_sfflags; int /*<<< orphan*/  kn_sdata; } ;
struct kevent_internal_s {int /*<<< orphan*/  fflags; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 int filt_tty_common (struct knote*,struct tty*) ; 
 int /*<<< orphan*/  knote_set_error (struct knote*,int /*<<< orphan*/ ) ; 
 struct tty* tty_lock_from_knote (struct knote*) ; 
 int /*<<< orphan*/  tty_unlock (struct tty*) ; 

__attribute__((used)) static int
filt_ttytouch(struct knote *kn, struct kevent_internal_s *kev)
{
	struct tty *tp;
	int res = 0;

	tp = tty_lock_from_knote(kn);
	if (!tp) {
		knote_set_error(kn, ENOENT);
		return 0;
	}

	kn->kn_sdata = kev->data;
	kn->kn_sfflags = kev->fflags;

	if (kn->kn_vnode_kqok) {
		res = filt_tty_common(kn, tp);
	}

	tty_unlock(tp);

	return res;
}