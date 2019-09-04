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
struct knote {int kn_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 int EV_EOF ; 
 int EV_ONESHOT ; 
 long NOTE_REVOKE ; 
 int filt_tty_common (struct knote*,struct tty*) ; 
 int /*<<< orphan*/  knote_set_error (struct knote*,int /*<<< orphan*/ ) ; 
 struct tty* tty_from_knote (struct knote*) ; 
 int /*<<< orphan*/  tty_lock (struct tty*) ; 
 int /*<<< orphan*/  tty_unlock (struct tty*) ; 

__attribute__((used)) static int
filt_ttyevent(struct knote *kn, long hint)
{
	int ret;
	struct tty *tp;
	bool revoked = hint & NOTE_REVOKE;
	hint &= ~NOTE_REVOKE;

	tp = tty_from_knote(kn);
	if (!tp) {
		knote_set_error(kn, ENOENT);
		return 0;
	}

	if (!hint) {
		tty_lock(tp);
	}

	if (revoked) {
		kn->kn_flags |= EV_EOF | EV_ONESHOT;
		ret = 1;
	} else {
		ret = filt_tty_common(kn, tp);
	}

	if (!hint) {
		tty_unlock(tp);
	}

	return ret;
}