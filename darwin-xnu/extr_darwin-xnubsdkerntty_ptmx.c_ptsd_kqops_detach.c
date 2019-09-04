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
struct TYPE_3__ {int /*<<< orphan*/  si_note; } ;
struct TYPE_4__ {int /*<<< orphan*/  si_note; } ;
struct tty {int t_state; TYPE_1__ t_wsel; TYPE_2__ t_rsel; } ;
struct knote {int kn_filter; struct tty* kn_hook; } ;

/* Variables and functions */
#define  EVFILT_READ 129 
#define  EVFILT_WRITE 128 
 int /*<<< orphan*/  KNOTE_DETACH (int /*<<< orphan*/ *,struct knote*) ; 
 int TS_ISOPEN ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,struct knote*,int) ; 
 int /*<<< orphan*/  tty_lock (struct tty*) ; 
 int /*<<< orphan*/  tty_unlock (struct tty*) ; 
 int /*<<< orphan*/  ttyfree (struct tty*) ; 

__attribute__((used)) static void
ptsd_kqops_detach(struct knote *kn)
{
	struct tty *tp;

	tp = kn->kn_hook;
	assert(tp != NULL);

	tty_lock(tp);

	/*
	 * Only detach knotes from open ttys -- ttyclose detaches all knotes
	 * under the lock and unsets TS_ISOPEN.
	 */
	if (tp->t_state & TS_ISOPEN) {
		switch (kn->kn_filter) {
		case EVFILT_READ:
			KNOTE_DETACH(&tp->t_rsel.si_note, kn);
			break;

		case EVFILT_WRITE:
			KNOTE_DETACH(&tp->t_wsel.si_note, kn);
			break;

		default:
			panic("invalid knote %p detach, filter: %d", kn, kn->kn_filter);
			break;
		}
	}

	kn->kn_hook = NULL;
	tty_unlock(tp);

	ttyfree(tp);
}