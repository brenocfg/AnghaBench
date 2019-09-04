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
struct TYPE_3__ {int sb_flags; TYPE_2__ sb_sel; } ;
struct socket {TYPE_1__ so_rcv; int /*<<< orphan*/  so_pgid; } ;

/* Variables and functions */
 int /*<<< orphan*/  KNOTE (int /*<<< orphan*/ *,int) ; 
 int NOTE_OOB ; 
 int SB_KNOTE ; 
 int /*<<< orphan*/  SIGURG ; 
 int SO_FILT_HINT_LOCKED ; 
 int /*<<< orphan*/  gsignal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  selwakeup (TYPE_2__*) ; 

void
sohasoutofband(struct socket *so)
{
	if (so->so_pgid < 0)
		gsignal(-so->so_pgid, SIGURG);
	else if (so->so_pgid > 0)
		proc_signal(so->so_pgid, SIGURG);
	selwakeup(&so->so_rcv.sb_sel);
	if (so->so_rcv.sb_flags & SB_KNOTE) {
		KNOTE(&so->so_rcv.sb_sel.si_note,
		    (NOTE_OOB | SO_FILT_HINT_LOCKED));
	}
}