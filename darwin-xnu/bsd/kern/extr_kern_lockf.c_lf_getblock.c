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
struct lockf {int lf_flags; scalar_t__ lf_type; int /*<<< orphan*/  lf_owner; struct lockf* lf_next; struct lockf** lf_head; } ;
typedef  int pid_t ;

/* Variables and functions */
 int F_OFD_LOCK ; 
 int F_POSIX ; 
 scalar_t__ F_WRLCK ; 
 struct lockf* NOLOCKF ; 
 int /*<<< orphan*/  OTHERS ; 
 scalar_t__ OVERLAP_NONE ; 
 scalar_t__ lf_findoverlap (struct lockf*,struct lockf*,int /*<<< orphan*/ ,struct lockf***,struct lockf**) ; 
 int proc_pid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct lockf *
lf_getblock(struct lockf *lock, pid_t matchpid)
{
	struct lockf **prev, *overlap, *lf = *(lock->lf_head);

	for (prev = lock->lf_head;
	    lf_findoverlap(lf, lock, OTHERS, &prev, &overlap) != OVERLAP_NONE;
	    lf = overlap->lf_next) {
		/*
		 * Found an overlap.
		 *
		 * If we're matching pids, and it's a record lock,
		 * or it's an OFD lock on a process-confined fd,
		 * but the pid doesn't match, then keep on looking ..
		 */
		if (matchpid != -1 &&
		    (overlap->lf_flags & (F_POSIX|F_OFD_LOCK)) != 0 &&
		    proc_pid(overlap->lf_owner) != matchpid)
			continue;

		/*
		 * does it block us?
		 */
		if ((lock->lf_type == F_WRLCK || overlap->lf_type == F_WRLCK))
			return (overlap);
	}
	return (NOLOCKF);
}