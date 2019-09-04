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

/* Variables and functions */
 scalar_t__ KERN_SUCCESS ; 
 scalar_t__ TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 scalar_t__ kernel_thread_start (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_buf_delwri_service () ; 
 int /*<<< orphan*/  nfs_buf_delwri_thread ; 
 int /*<<< orphan*/  nfs_buf_mutex ; 
 int /*<<< orphan*/  nfsbufdelwri ; 
 scalar_t__ nfsbufdelwrithd ; 
 int /*<<< orphan*/  thread_deallocate (scalar_t__) ; 
 int /*<<< orphan*/  wakeup (scalar_t__*) ; 

void
nfs_buf_delwri_push(int locked)
{
	if (TAILQ_EMPTY(&nfsbufdelwri))
		return;
	if (!locked)
		lck_mtx_lock(nfs_buf_mutex);
	/* wake up the delayed write service thread */
	if (nfsbufdelwrithd)
		wakeup(&nfsbufdelwrithd);
	else if (kernel_thread_start(nfs_buf_delwri_thread, NULL, &nfsbufdelwrithd) == KERN_SUCCESS)
		thread_deallocate(nfsbufdelwrithd);
	/* otherwise, try to do some of the work ourselves */
	if (!nfsbufdelwrithd)
		nfs_buf_delwri_service();
	if (!locked)
		lck_mtx_unlock(nfs_buf_mutex);
}