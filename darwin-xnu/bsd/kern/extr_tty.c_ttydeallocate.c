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
struct TYPE_4__ {int /*<<< orphan*/  si_note; } ;
struct TYPE_3__ {int /*<<< orphan*/  si_note; } ;
struct tty {int /*<<< orphan*/  t_lock; int /*<<< orphan*/  t_outq; int /*<<< orphan*/  t_canq; int /*<<< orphan*/  t_rawq; TYPE_2__ t_wsel; TYPE_1__ t_rsel; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (struct tty*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_TTYS ; 
 scalar_t__ SLIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TTY_LOCK_NOTOWNED (struct tty*) ; 
 int /*<<< orphan*/  clfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  tty_lck_grp ; 

__attribute__((used)) static void
ttydeallocate(struct tty *tp)
{
	TTY_LOCK_NOTOWNED(tp);	/* debug assert */

#if DEBUG
	if (!(SLIST_EMPTY(&tp->t_rsel.si_note) && SLIST_EMPTY(&tp->t_wsel.si_note))) {
		panic("knotes hooked into a tty when the tty is freed.\n");
	}
#endif /* DEBUG */

	clfree(&tp->t_rawq);
	clfree(&tp->t_canq);
	clfree(&tp->t_outq);
	lck_mtx_destroy(&tp->t_lock, tty_lck_grp);
	FREE(tp, M_TTYS);
}