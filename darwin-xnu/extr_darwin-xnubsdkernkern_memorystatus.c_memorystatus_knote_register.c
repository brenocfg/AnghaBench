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
struct knote {unsigned int kn_sfflags; } ;

/* Variables and functions */
 int ENOTSUP ; 
 unsigned int EVFILT_MEMORYSTATUS_ALL_MASK ; 
 int /*<<< orphan*/  KNOTE_ATTACH (int /*<<< orphan*/ *,struct knote*) ; 
 int NOTE_MEMORYSTATUS_PROC_LIMIT_CRITICAL ; 
 int NOTE_MEMORYSTATUS_PROC_LIMIT_CRITICAL_ACTIVE ; 
 int NOTE_MEMORYSTATUS_PROC_LIMIT_CRITICAL_INACTIVE ; 
 int NOTE_MEMORYSTATUS_PROC_LIMIT_WARN ; 
 int NOTE_MEMORYSTATUS_PROC_LIMIT_WARN_ACTIVE ; 
 int NOTE_MEMORYSTATUS_PROC_LIMIT_WARN_INACTIVE ; 
 int /*<<< orphan*/  memorystatus_klist ; 
 int /*<<< orphan*/  memorystatus_klist_lock () ; 
 int /*<<< orphan*/  memorystatus_klist_unlock () ; 

int
memorystatus_knote_register(struct knote *kn) {
	int error = 0;

	memorystatus_klist_lock();

	/*
	 * Support only userspace visible flags.
	 */
    if ((kn->kn_sfflags & EVFILT_MEMORYSTATUS_ALL_MASK) == (unsigned int) kn->kn_sfflags) {

#if !CONFIG_EMBEDDED
		if (kn->kn_sfflags & NOTE_MEMORYSTATUS_PROC_LIMIT_WARN) {
			kn->kn_sfflags |= NOTE_MEMORYSTATUS_PROC_LIMIT_WARN_ACTIVE;
			kn->kn_sfflags |= NOTE_MEMORYSTATUS_PROC_LIMIT_WARN_INACTIVE;
		}

		if (kn->kn_sfflags & NOTE_MEMORYSTATUS_PROC_LIMIT_CRITICAL) {
			kn->kn_sfflags |= NOTE_MEMORYSTATUS_PROC_LIMIT_CRITICAL_ACTIVE;
			kn->kn_sfflags |= NOTE_MEMORYSTATUS_PROC_LIMIT_CRITICAL_INACTIVE;
		}
#endif /* !CONFIG_EMBEDDED */

		KNOTE_ATTACH(&memorystatus_klist, kn);

	} else {	  
		error = ENOTSUP;
	}
	
	memorystatus_klist_unlock();
	
	return error;
}