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
struct tty {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  si_note; } ;
struct TYPE_4__ {int /*<<< orphan*/  si_note; } ;
struct ptmx_ioctl {TYPE_1__ pt_selw; TYPE_2__ pt_selr; struct tty* pt_tty; } ;
struct knote {int kn_filter; struct ptmx_ioctl* kn_hook; } ;

/* Variables and functions */
#define  EVFILT_READ 129 
#define  EVFILT_WRITE 128 
 int /*<<< orphan*/  KNOTE_DETACH (int /*<<< orphan*/ *,struct knote*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,struct knote*,int) ; 
 int /*<<< orphan*/  tty_lock (struct tty*) ; 
 int /*<<< orphan*/  tty_unlock (struct tty*) ; 
 int /*<<< orphan*/  ttyfree (struct tty*) ; 

__attribute__((used)) static void
ptmx_kqops_detach(struct knote *kn)
{
	struct ptmx_ioctl *pti = kn->kn_hook;
	struct tty *tp = pti->pt_tty;

	assert(tp != NULL);

	tty_lock(tp);

	switch (kn->kn_filter) {
	case EVFILT_READ:
		KNOTE_DETACH(&pti->pt_selr.si_note, kn);
		break;

	case EVFILT_WRITE:
		KNOTE_DETACH(&pti->pt_selw.si_note, kn);
		break;

	default:
		panic("invalid knote %p detach, filter: %d", kn, kn->kn_filter);
		break;
	}

	kn->kn_hook = NULL;
	tty_unlock(tp);

	ttyfree(tp);
}