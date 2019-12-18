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
struct socket {int so_flags; } ;
struct mppcb {int /*<<< orphan*/  mpp_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPPCB_STATE_DEAD ; 
 int SOF_PCBCLEARING ; 
 int /*<<< orphan*/  mp_gc_sched () ; 
 struct mppcb* mpsotomppcb (struct socket*) ; 

void
mp_pcbdetach(struct socket *mp_so)
{
	struct mppcb *mpp = mpsotomppcb(mp_so);

	mpp->mpp_state = MPPCB_STATE_DEAD;
	if (!(mp_so->so_flags & SOF_PCBCLEARING))
		mp_so->so_flags |= SOF_PCBCLEARING;

	mp_gc_sched();
}