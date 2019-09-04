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
 int PSPIN ; 
 int PVFS ; 
 int /*<<< orphan*/  lck_mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int*,int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
vn_offset_lock(struct fileglob *fg)
{
	lck_mtx_lock_spin(&fg->fg_lock);
	while (fg->fg_lflags & FG_OFF_LOCKED) {
		fg->fg_lflags |= FG_OFF_LOCKWANT;
		msleep(&fg->fg_lflags, &fg->fg_lock, PVFS | PSPIN,
		    "fg_offset_lock_wait", 0);
	}
	fg->fg_lflags |= FG_OFF_LOCKED;
	lck_mtx_unlock(&fg->fg_lock);
}