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
struct lockf {int lf_start; int lf_end; int /*<<< orphan*/ * lf_owner; int /*<<< orphan*/  lf_type; } ;
struct flock {int l_start; int l_len; int l_pid; int /*<<< orphan*/  l_type; int /*<<< orphan*/  l_whence; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  F_UNLCK ; 
 int LF_DBG_LOCKOP ; 
 int /*<<< orphan*/  SEEK_SET ; 
 struct lockf* lf_getblock (struct lockf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lf_print (char*,struct lockf*) ; 
 int lockf_debug ; 
 int proc_pid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
lf_getlock(struct lockf *lock, struct flock *fl, pid_t matchpid)
{
	struct lockf *block;

#ifdef LOCKF_DEBUGGING
	if (lockf_debug & LF_DBG_LOCKOP)
		lf_print("lf_getlock", lock);
#endif /* LOCKF_DEBUGGING */

	if ((block = lf_getblock(lock, matchpid))) {
		fl->l_type = block->lf_type;
		fl->l_whence = SEEK_SET;
		fl->l_start = block->lf_start;
		if (block->lf_end == -1)
			fl->l_len = 0;
		else
			fl->l_len = block->lf_end - block->lf_start + 1;
		if (NULL != block->lf_owner) {
			/*
			 * lf_owner is only non-NULL when the lock
			 * "owner" can be unambiguously determined
			 */
			fl->l_pid = proc_pid(block->lf_owner);
		} else
			fl->l_pid = -1;
	} else {
		fl->l_type = F_UNLCK;
	}
	return (0);
}