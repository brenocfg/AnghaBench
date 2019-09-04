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
struct knote {scalar_t__ kn_fflags; int /*<<< orphan*/  kn_sfflags; } ;
struct kevent_internal_s {int /*<<< orphan*/  fflags; } ;

/* Variables and functions */
 int /*<<< orphan*/  fs_klist_lock ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
filt_fstouch(struct knote *kn, struct kevent_internal_s *kev)
{
	int res;

	lck_mtx_lock(fs_klist_lock);

	kn->kn_sfflags = kev->fflags;

	/*
	 * the above filter function sets bits even if nobody is looking for them.
	 * Just preserve those bits even in the new mask is more selective
	 * than before.
	 *
	 * For compatibility with previous implementations, we leave kn_fflags
	 * as they were before.
	 */
	//if (kn->kn_sfflags)
	//	kn->kn_fflags &= kn->kn_sfflags;
	res = (kn->kn_fflags != 0);

	lck_mtx_unlock(fs_klist_lock);

	return res;
}