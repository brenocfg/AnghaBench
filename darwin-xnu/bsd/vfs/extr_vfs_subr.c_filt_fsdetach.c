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
struct knote {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KNOTE_DETACH (int /*<<< orphan*/ *,struct knote*) ; 
 int /*<<< orphan*/  fs_klist ; 
 int /*<<< orphan*/  fs_klist_lock ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
filt_fsdetach(struct knote *kn)
{
	lck_mtx_lock(fs_klist_lock);
	KNOTE_DETACH(&fs_klist, kn);
	lck_mtx_unlock(fs_klist_lock);
}