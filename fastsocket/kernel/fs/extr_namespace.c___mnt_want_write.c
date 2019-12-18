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
struct vfsmount {int mnt_flags; } ;

/* Variables and functions */
 int EROFS ; 
 int MNT_WRITE_HOLD ; 
 scalar_t__ __mnt_is_readonly (struct vfsmount*) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  dec_mnt_writers (struct vfsmount*) ; 
 int /*<<< orphan*/  inc_mnt_writers (struct vfsmount*) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  smp_rmb () ; 

int __mnt_want_write(struct vfsmount *mnt)
{
	int ret = 0;

	preempt_disable();
	inc_mnt_writers(mnt);
	/*
	 * The store to inc_mnt_writers must be visible before we pass
	 * MNT_WRITE_HOLD loop below, so that the slowpath can see our
	 * incremented count after it has set MNT_WRITE_HOLD.
	 */
	smp_mb();
	while (mnt->mnt_flags & MNT_WRITE_HOLD)
		cpu_relax();
	/*
	 * After the slowpath clears MNT_WRITE_HOLD, mnt_is_readonly will
	 * be set to match its requirements. So we must not load that until
	 * MNT_WRITE_HOLD is cleared.
	 */
	smp_rmb();
	if (__mnt_is_readonly(mnt)) {
		dec_mnt_writers(mnt);
		ret = -EROFS;
		goto out;
	}
out:
	preempt_enable();

	return ret;
}