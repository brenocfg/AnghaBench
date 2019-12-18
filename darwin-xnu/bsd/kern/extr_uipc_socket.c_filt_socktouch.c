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
typedef  int uint32_t ;
struct socket {int dummy; } ;
struct knote {int kn_sfflags; int kn_hookid; int /*<<< orphan*/  kn_sdata; TYPE_2__* kn_fp; } ;
struct kevent_internal_s {int fflags; int /*<<< orphan*/  data; } ;
struct TYPE_4__ {TYPE_1__* f_fglob; } ;
struct TYPE_3__ {scalar_t__ fg_data; } ;

/* Variables and functions */
 int EVFILT_SOCK_LEVEL_TRIGGER_MASK ; 
 int filt_sockev_common (struct knote*,struct socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_lock (struct socket*,int) ; 
 int /*<<< orphan*/  socket_unlock (struct socket*,int) ; 

__attribute__((used)) static int
filt_socktouch(
	struct knote *kn,
	struct kevent_internal_s *kev)
{
	struct socket *so = (struct socket *)kn->kn_fp->f_fglob->fg_data;
	uint32_t changed_flags;
	int ret;

	socket_lock(so, 1);

	/* save off the [result] data and fflags */
	changed_flags = (kn->kn_sfflags ^ kn->kn_hookid);

	/* save off the new input fflags and data */
	kn->kn_sfflags = kev->fflags;
	kn->kn_sdata = kev->data;

	/* restrict the current results to the (smaller?) set of new interest */
	/*
	 * For compatibility with previous implementations, we leave kn_fflags
	 * as they were before.
	 */
	//kn->kn_fflags &= kev->fflags;

	/*
	 * Since we keep track of events that are already
	 * delivered, if any of those events are not requested
	 * anymore the state related to them can be reset
	 */
	kn->kn_hookid &=
	    ~(changed_flags & EVFILT_SOCK_LEVEL_TRIGGER_MASK);

	/* determine if we have events to deliver */
	ret = filt_sockev_common(kn, so, 0);

	socket_unlock(so, 1);

	return ret;
}