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
struct selinfo {int /*<<< orphan*/  si_note; } ;
struct tty {struct selinfo t_wsel; struct selinfo t_rsel; } ;
struct knote {int /*<<< orphan*/ * kn_hook; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
#define  FREAD 129 
#define  FWRITE 128 
 int /*<<< orphan*/  KNOTE_DETACH (int /*<<< orphan*/ *,struct knote*) ; 
 int knote_get_seltype (struct knote*) ; 
 int /*<<< orphan*/  knote_set_error (struct knote*,int /*<<< orphan*/ ) ; 
 struct tty* tty_lock_from_knote (struct knote*) ; 
 int /*<<< orphan*/  tty_unlock (struct tty*) ; 
 int /*<<< orphan*/  ttyfree (struct tty*) ; 

__attribute__((used)) static void
filt_ttydetach(struct knote *kn)
{
	struct tty *tp;

	tp = tty_lock_from_knote(kn);
	if (!tp) {
		knote_set_error(kn, ENOENT);
		return;
	}

	struct selinfo *si = NULL;
	switch (knote_get_seltype(kn)) {
	case FREAD:
		si = &tp->t_rsel;
		break;
	case FWRITE:
		si = &tp->t_wsel;
		break;
	/* knote_get_seltype will panic on default */
	}

	KNOTE_DETACH(&si->si_note, kn);
	kn->kn_hook = NULL;

	tty_unlock(tp);
	ttyfree(tp);
}