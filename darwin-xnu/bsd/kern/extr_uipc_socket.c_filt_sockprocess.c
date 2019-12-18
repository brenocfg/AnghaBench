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
struct socket {int dummy; } ;
struct kevent_internal_s {int dummy; } ;
struct knote {int kn_fflags; int kn_hookid; int kn_flags; scalar_t__ kn_data; struct kevent_internal_s kn_kevent; TYPE_2__* kn_fp; } ;
struct filt_process_s {int dummy; } ;
struct TYPE_4__ {TYPE_1__* f_fglob; } ;
struct TYPE_3__ {scalar_t__ fg_data; } ;

/* Variables and functions */
 int EVFILT_SOCK_LEVEL_TRIGGER_MASK ; 
 int EV_CLEAR ; 
 int NOTE_RESUME ; 
 int NOTE_SUSPEND ; 
 int filt_sockev_common (struct knote*,struct socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_lock (struct socket*,int) ; 
 int /*<<< orphan*/  socket_unlock (struct socket*,int) ; 

__attribute__((used)) static int
filt_sockprocess(
	struct knote *kn,
	struct filt_process_s *data,
	struct kevent_internal_s *kev)
{
#pragma unused(data)

	struct socket *so = (struct socket *)kn->kn_fp->f_fglob->fg_data;
	int ret = 0;

	socket_lock(so, 1);

	ret = filt_sockev_common(kn, so, 0);
	if (ret) {
		*kev = kn->kn_kevent;

		/*
		 * Store the state of the events being delivered. This
		 * state can be used to deliver level triggered events
		 * ateast once and still avoid waking up the application
		 * multiple times as long as the event is active.
		 */
		if (kn->kn_fflags != 0)
			kn->kn_hookid |= (kn->kn_fflags &
					  EVFILT_SOCK_LEVEL_TRIGGER_MASK);

		/*
		 * NOTE_RESUME and NOTE_SUSPEND are an exception, deliver
		 * only one of them and remember the last one that was
		 * delivered last
		 */
		if (kn->kn_fflags & NOTE_SUSPEND)
			kn->kn_hookid &= ~NOTE_RESUME;
		if (kn->kn_fflags & NOTE_RESUME)
			kn->kn_hookid &= ~NOTE_SUSPEND;

		if (kn->kn_flags & EV_CLEAR) {
			kn->kn_data = 0;
			kn->kn_fflags = 0;
		}
	}

	socket_unlock(so, 1);

	return ret;
}