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
struct fileglob {int fg_lflags; int /*<<< orphan*/  fg_lock; } ;

/* Variables and functions */
 int FG_OFF_LOCKED ; 
 int FG_OFF_LOCKWANT ; 
 int /*<<< orphan*/  lck_mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup (int*) ; 

__attribute__((used)) static inline void
vn_offset_unlock(struct fileglob *fg)
{
	int lock_wanted = 0;

	lck_mtx_lock_spin(&fg->fg_lock);
	if (fg->fg_lflags & FG_OFF_LOCKWANT) {
		lock_wanted = 1;
	}
	fg->fg_lflags &= ~(FG_OFF_LOCKED | FG_OFF_LOCKWANT);
	lck_mtx_unlock(&fg->fg_lock);
	if (lock_wanted) {
		wakeup(&fg->fg_lflags);
	}
}