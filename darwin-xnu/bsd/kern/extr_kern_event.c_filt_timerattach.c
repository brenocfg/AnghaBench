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
typedef  int /*<<< orphan*/ * thread_call_t ;
typedef  int /*<<< orphan*/  thread_call_param_t ;
struct knote {int kn_sfflags; int /*<<< orphan*/  kn_hookid; int /*<<< orphan*/  kn_flags; int /*<<< orphan*/ * kn_hook; } ;
struct kevent_internal_s {int dummy; } ;
struct filt_timer_params {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  EV_CLEAR ; 
 int /*<<< orphan*/  EV_ONESHOT ; 
 int FILTER_ACTIVE ; 
 int NOTE_ABSOLUTE ; 
 int /*<<< orphan*/  THREAD_CALL_OPTIONS_ONCE ; 
 int /*<<< orphan*/  THREAD_CALL_PRIORITY_HIGH ; 
 int /*<<< orphan*/  TIMER_IDLE ; 
 int /*<<< orphan*/  TIMER_IMMEDIATE ; 
 scalar_t__ filt_timer_is_ready (struct knote*) ; 
 int /*<<< orphan*/  filt_timer_set_params (struct knote*,struct filt_timer_params*) ; 
 int /*<<< orphan*/  filt_timerarm (struct knote*) ; 
 int /*<<< orphan*/  filt_timerexpire ; 
 int filt_timervalidate (struct kevent_internal_s*,struct filt_timer_params*) ; 
 int /*<<< orphan*/  knote_set_error (struct knote*,int) ; 
 int /*<<< orphan*/  os_atomic_store (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  relaxed ; 
 int /*<<< orphan*/ * thread_call_allocate_with_options (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
filt_timerattach(struct knote *kn, struct kevent_internal_s *kev)
{
	thread_call_t callout;
	struct filt_timer_params params;
	int error;

	if ((error = filt_timervalidate(kev, &params)) != 0) {
		knote_set_error(kn, error);
		return 0;
	}

	callout = thread_call_allocate_with_options(filt_timerexpire,
	                (thread_call_param_t)kn, THREAD_CALL_PRIORITY_HIGH,
	                THREAD_CALL_OPTIONS_ONCE);

	if (NULL == callout) {
		knote_set_error(kn, ENOMEM);
		return 0;
	}

	filt_timer_set_params(kn, &params);
	kn->kn_hook = callout;
	kn->kn_flags |= EV_CLEAR;
	os_atomic_store(&kn->kn_hookid, TIMER_IDLE, relaxed);

	/* NOTE_ABSOLUTE implies EV_ONESHOT */
	if (kn->kn_sfflags & NOTE_ABSOLUTE)
		kn->kn_flags |= EV_ONESHOT;

	if (filt_timer_is_ready(kn)) {
		os_atomic_store(&kn->kn_hookid, TIMER_IMMEDIATE, relaxed);
		return FILTER_ACTIVE;
	} else {
		filt_timerarm(kn);
		return 0;
	}
}