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
struct knote {int kn_sfflags; scalar_t__ kn_fflags; } ;
struct kevent_internal_s {int fflags; } ;

/* Variables and functions */
 int EVFILT_MEMORYSTATUS_ALL_MASK ; 
 int NOTE_MEMORYSTATUS_PROC_LIMIT_CRITICAL ; 
 int NOTE_MEMORYSTATUS_PROC_LIMIT_CRITICAL_ACTIVE ; 
 int NOTE_MEMORYSTATUS_PROC_LIMIT_CRITICAL_INACTIVE ; 
 int NOTE_MEMORYSTATUS_PROC_LIMIT_WARN ; 
 int NOTE_MEMORYSTATUS_PROC_LIMIT_WARN_ACTIVE ; 
 int NOTE_MEMORYSTATUS_PROC_LIMIT_WARN_INACTIVE ; 
 int /*<<< orphan*/  memorystatus_klist_lock () ; 
 int /*<<< orphan*/  memorystatus_klist_unlock () ; 

__attribute__((used)) static int
filt_memorystatustouch(struct knote *kn, struct kevent_internal_s *kev)
{
	int res;
	int prev_kn_sfflags = 0;

	memorystatus_klist_lock();

	/*
	 * copy in new kevent settings
	 * (saving the "desired" data and fflags).
	 */

	prev_kn_sfflags = kn->kn_sfflags;
	kn->kn_sfflags = (kev->fflags & EVFILT_MEMORYSTATUS_ALL_MASK);

#if !CONFIG_EMBEDDED
	/*
	 * Only on desktop do we restrict notifications to
	 * one per active/inactive state (soft limits only).
	 */
	if (kn->kn_sfflags & NOTE_MEMORYSTATUS_PROC_LIMIT_WARN) {
		/*
		 * Is there previous state to preserve?
		 */
		if (prev_kn_sfflags & NOTE_MEMORYSTATUS_PROC_LIMIT_WARN) {
			/*
			 * This knote was previously interested in proc_limit_warn,
			 * so yes, preserve previous state.
			 */
			if (prev_kn_sfflags & NOTE_MEMORYSTATUS_PROC_LIMIT_WARN_ACTIVE) {
				kn->kn_sfflags |= NOTE_MEMORYSTATUS_PROC_LIMIT_WARN_ACTIVE;
			}
			if (prev_kn_sfflags & NOTE_MEMORYSTATUS_PROC_LIMIT_WARN_INACTIVE) {
				kn->kn_sfflags |= NOTE_MEMORYSTATUS_PROC_LIMIT_WARN_INACTIVE;
			}
		} else {
			/*
			 * This knote was not previously interested in proc_limit_warn,
			 * but it is now.  Set both states.
			 */
			kn->kn_sfflags |= NOTE_MEMORYSTATUS_PROC_LIMIT_WARN_ACTIVE;
			kn->kn_sfflags |= NOTE_MEMORYSTATUS_PROC_LIMIT_WARN_INACTIVE;
		}
	}

	if (kn->kn_sfflags & NOTE_MEMORYSTATUS_PROC_LIMIT_CRITICAL) {
		/*
		 * Is there previous state to preserve?
		 */
		if (prev_kn_sfflags & NOTE_MEMORYSTATUS_PROC_LIMIT_CRITICAL) {
			/*
			 * This knote was previously interested in proc_limit_critical,
			 * so yes, preserve previous state.
			 */
			if (prev_kn_sfflags & NOTE_MEMORYSTATUS_PROC_LIMIT_CRITICAL_ACTIVE) {
				kn->kn_sfflags |= NOTE_MEMORYSTATUS_PROC_LIMIT_CRITICAL_ACTIVE;
			}
			if (prev_kn_sfflags & NOTE_MEMORYSTATUS_PROC_LIMIT_CRITICAL_INACTIVE) {
				kn->kn_sfflags |= NOTE_MEMORYSTATUS_PROC_LIMIT_CRITICAL_INACTIVE;
			}
		} else {
			/*
			 * This knote was not previously interested in proc_limit_critical,
			 * but it is now.  Set both states.
			 */
			kn->kn_sfflags |= NOTE_MEMORYSTATUS_PROC_LIMIT_CRITICAL_ACTIVE;
			kn->kn_sfflags |= NOTE_MEMORYSTATUS_PROC_LIMIT_CRITICAL_INACTIVE;
		}
	}
#endif /* !CONFIG_EMBEDDED */

	/*
	 * reset the output flags based on a
	 * combination of the old events and
	 * the new desired event list.
	 */
	//kn->kn_fflags &= kn->kn_sfflags;

	res = (kn->kn_fflags != 0);

	memorystatus_klist_unlock();

	return res;
}