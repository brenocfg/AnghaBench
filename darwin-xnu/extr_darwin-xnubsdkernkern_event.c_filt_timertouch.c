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
typedef  int uint32_t ;
struct knote {int kn_sfflags; int /*<<< orphan*/  kn_hookid; } ;
struct kevent_internal_s {int fflags; int data; int /*<<< orphan*/  flags; } ;
struct filt_timer_params {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  EV_ERROR ; 
 int FILTER_ACTIVE ; 
 int FILTER_UPDATE_REQ_QOS ; 
 int NOTE_ABSOLUTE ; 
 int /*<<< orphan*/  TIMER_IMMEDIATE ; 
 scalar_t__ filt_timer_is_ready (struct knote*) ; 
 int /*<<< orphan*/  filt_timer_set_params (struct knote*,struct filt_timer_params*) ; 
 int /*<<< orphan*/  filt_timerarm (struct knote*) ; 
 int /*<<< orphan*/  filt_timercancel (struct knote*) ; 
 int filt_timervalidate (struct kevent_internal_s*,struct filt_timer_params*) ; 
 int /*<<< orphan*/  os_atomic_store (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  relaxed ; 

__attribute__((used)) static int
filt_timertouch(struct knote *kn, struct kevent_internal_s *kev)
{
	struct filt_timer_params params;
	uint32_t changed_flags = (kn->kn_sfflags ^ kev->fflags);
	int error;

	if (changed_flags & NOTE_ABSOLUTE) {
		kev->flags |= EV_ERROR;
		kev->data = EINVAL;
		return 0;
	}

	if ((error = filt_timervalidate(kev, &params)) != 0) {
		kev->flags |= EV_ERROR;
		kev->data = error;
		return 0;
	}

	/* capture the new values used to compute deadline */
	filt_timercancel(kn);
	filt_timer_set_params(kn, &params);
	kn->kn_sfflags = kev->fflags;

	if (filt_timer_is_ready(kn)) {
		os_atomic_store(&kn->kn_hookid, TIMER_IMMEDIATE, relaxed);
		return FILTER_ACTIVE | FILTER_UPDATE_REQ_QOS;
	} else {
		filt_timerarm(kn);
		return FILTER_UPDATE_REQ_QOS;
	}
}