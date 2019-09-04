#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ sb_cc; } ;
struct TYPE_4__ {scalar_t__ sb_cc; } ;
struct socket {int so_flags1; TYPE_2__ so_snd; TYPE_1__ so_rcv; } ;
struct TYPE_6__ {int /*<<< orphan*/  so_xbkidle_drained; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSIncrementAtomic (int /*<<< orphan*/ *) ; 
 int SOF1_EXTEND_BK_IDLE_INPROG ; 
 int /*<<< orphan*/  so_stop_extended_bk_idle (struct socket*) ; 
 TYPE_3__ soextbkidlestat ; 

void
so_drain_extended_bk_idle(struct socket *so)
{
	if (so && (so->so_flags1 & SOF1_EXTEND_BK_IDLE_INPROG)) {
		/*
		 * Only penalize sockets that have outstanding data
		 */
		if (so->so_rcv.sb_cc || so->so_snd.sb_cc) {
			so_stop_extended_bk_idle(so);

			OSIncrementAtomic(&soextbkidlestat.so_xbkidle_drained);
		}
	}
}