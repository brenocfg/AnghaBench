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
typedef  int /*<<< orphan*/  thread_t ;
typedef  scalar_t__ kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_INFO (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  PERF_PET_THREAD ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ kernel_thread_start (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kperf_lck_grp ; 
 int /*<<< orphan*/  lck_mtx_alloc_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ pet_initted ; 
 int /*<<< orphan*/  pet_lock ; 
 int /*<<< orphan*/  pet_thread_loop ; 
 int /*<<< orphan*/  thread_deallocate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_set_thread_name (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static kern_return_t
pet_init(void)
{
	if (pet_initted) {
		return KERN_SUCCESS;
	}

	/* make the sync point */
	pet_lock = lck_mtx_alloc_init(&kperf_lck_grp, NULL);
	assert(pet_lock);

	/* create the thread */

	BUF_INFO(PERF_PET_THREAD, 0);
	thread_t t;
	kern_return_t kr = kernel_thread_start(pet_thread_loop, NULL, &t);
	if (kr != KERN_SUCCESS) {
		lck_mtx_free(pet_lock, &kperf_lck_grp);
		return kr;
	}

	thread_set_thread_name(t, "kperf sampling");
	/* let the thread hold the only reference */
	thread_deallocate(t);

	pet_initted = TRUE;

	return KERN_SUCCESS;
}