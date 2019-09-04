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
typedef  scalar_t__ vm_offset_t ;
struct image_params {int /*<<< orphan*/ * ip_strings; } ;
typedef  scalar_t__ kern_return_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ FALSE ; 
 scalar_t__ KERN_SUCCESS ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__* execargs_cache ; 
 int execargs_cache_size ; 
 int /*<<< orphan*/  execargs_free_count ; 
 int /*<<< orphan*/  execargs_lock_lock () ; 
 int /*<<< orphan*/  execargs_lock_unlock () ; 
 scalar_t__ execargs_purgeable_volatilize (int /*<<< orphan*/ *) ; 
 scalar_t__ execargs_waiters ; 
 int /*<<< orphan*/  execargs_wakeup_waiters () ; 

__attribute__((used)) static int
execargs_free(struct image_params *imgp)
{
	kern_return_t kret;
	int i;
	boolean_t needs_wakeup = FALSE;
	
	kret = execargs_purgeable_volatilize(imgp->ip_strings);

	execargs_lock_lock();
	execargs_free_count++;

	for (i = 0; i < execargs_cache_size; i++) {
		vm_offset_t element = execargs_cache[i];
		if (element == 0) {
			execargs_cache[i] = (vm_offset_t) imgp->ip_strings;
			imgp->ip_strings = NULL;
			break;
		}
	}

	assert(imgp->ip_strings == NULL);

	if (execargs_waiters > 0)
		needs_wakeup = TRUE;
	
	execargs_lock_unlock();

	if (needs_wakeup == TRUE)
		execargs_wakeup_waiters();

	return ((kret == KERN_SUCCESS ? 0 : EINVAL));
}