#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  si_note; } ;
struct TYPE_8__ {int sb_flags; TYPE_3__ sb_sel; } ;
struct socket {TYPE_4__ so_snd; } ;
struct knote {TYPE_2__* kn_fp; } ;
struct TYPE_6__ {TYPE_1__* f_fglob; } ;
struct TYPE_5__ {scalar_t__ fg_data; } ;

/* Variables and functions */
 scalar_t__ KNOTE_DETACH (int /*<<< orphan*/ *,struct knote*) ; 
 int SB_KNOTE ; 
 int /*<<< orphan*/  socket_lock (struct socket*,int) ; 
 int /*<<< orphan*/  socket_unlock (struct socket*,int) ; 

__attribute__((used)) static void
filt_sowdetach(struct knote *kn)
{
	struct socket *so = (struct socket *)kn->kn_fp->f_fglob->fg_data;
	socket_lock(so, 1);

	if (so->so_snd.sb_flags & SB_KNOTE)
		if (KNOTE_DETACH(&so->so_snd.sb_sel.si_note, kn))
			so->so_snd.sb_flags &= ~SB_KNOTE;
	socket_unlock(so, 1);
}