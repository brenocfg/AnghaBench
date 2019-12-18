#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* thread_t ;
typedef  int /*<<< orphan*/  clock_usec_t ;
typedef  int clock_sec_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_3__ {int options; int t_page_creation_throttled; int t_page_creation_count; int t_page_creation_time; int /*<<< orphan*/  t_page_creation_throttled_soft; int /*<<< orphan*/  t_page_creation_throttled_hard; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int HARD_THROTTLE_DELAY ; 
 scalar_t__ HARD_THROTTLE_LIMIT_REACHED () ; 
 scalar_t__ NEED_TO_HARD_THROTTLE_THIS_TASK () ; 
 int /*<<< orphan*/  OSAddAtomic (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSAddAtomic64 (int,int /*<<< orphan*/ *) ; 
 int SOFT_THROTTLE_DELAY ; 
 scalar_t__ SWAPPER_NEEDS_TO_UNTHROTTLE () ; 
 int TH_OPT_VMPRIV ; 
 scalar_t__ VM_CONFIG_COMPRESSOR_IS_PRESENT ; 
 int /*<<< orphan*/  VM_PAGEOUT_DEBUG (int /*<<< orphan*/ ,int) ; 
 int VM_PAGE_CREATION_THROTTLE_PERIOD_SECS ; 
 int VM_PAGE_CREATION_THROTTLE_RATE_PER_SEC ; 
 int /*<<< orphan*/  clock_get_system_microtime (int*,int /*<<< orphan*/ *) ; 
 TYPE_1__* current_thread () ; 
 int /*<<< orphan*/  vm_page_creation_throttle_avoided ; 
 int /*<<< orphan*/  vm_page_creation_throttled_hard ; 
 int /*<<< orphan*/  vm_page_creation_throttled_soft ; 
 scalar_t__ vm_page_free_count ; 
 scalar_t__ vm_page_free_wanted ; 
 scalar_t__ vm_page_free_wanted_privileged ; 
 int /*<<< orphan*/  vm_page_throttle_count ; 
 scalar_t__ vm_page_throttle_limit ; 

__attribute__((used)) static int
vm_page_throttled(boolean_t page_kept)
{
        clock_sec_t     elapsed_sec;
        clock_sec_t     tv_sec;
        clock_usec_t    tv_usec;

	thread_t thread = current_thread();

	if (thread->options & TH_OPT_VMPRIV)
		return (0);

	if (thread->t_page_creation_throttled) {
		thread->t_page_creation_throttled = 0;

		if (page_kept == FALSE)
			goto no_throttle;
	}
	if (NEED_TO_HARD_THROTTLE_THIS_TASK()) {
#if (DEVELOPMENT || DEBUG)
		thread->t_page_creation_throttled_hard++;
		OSAddAtomic(1, &vm_page_creation_throttled_hard);
#endif /* DEVELOPMENT || DEBUG */
		return (HARD_THROTTLE_DELAY);
	}

	if ((vm_page_free_count < vm_page_throttle_limit || (VM_CONFIG_COMPRESSOR_IS_PRESENT && SWAPPER_NEEDS_TO_UNTHROTTLE())) &&
	    thread->t_page_creation_count > (VM_PAGE_CREATION_THROTTLE_PERIOD_SECS * VM_PAGE_CREATION_THROTTLE_RATE_PER_SEC)) {

		if (vm_page_free_wanted == 0 && vm_page_free_wanted_privileged == 0) {
#if (DEVELOPMENT || DEBUG)
			OSAddAtomic64(1, &vm_page_creation_throttle_avoided);
#endif
			goto no_throttle;
		}
		clock_get_system_microtime(&tv_sec, &tv_usec);

		elapsed_sec = tv_sec - thread->t_page_creation_time;

		if (elapsed_sec <= VM_PAGE_CREATION_THROTTLE_PERIOD_SECS ||
		    (thread->t_page_creation_count / elapsed_sec) >= VM_PAGE_CREATION_THROTTLE_RATE_PER_SEC) {

			if (elapsed_sec >= (3 * VM_PAGE_CREATION_THROTTLE_PERIOD_SECS)) {
				/*
				 * we'll reset our stats to give a well behaved app
				 * that was unlucky enough to accumulate a bunch of pages
				 * over a long period of time a chance to get out of
				 * the throttled state... we reset the counter and timestamp
				 * so that if it stays under the rate limit for the next second
				 * it will be back in our good graces... if it exceeds it, it
				 * will remain in the throttled state
				 */
				thread->t_page_creation_time = tv_sec;
				thread->t_page_creation_count = VM_PAGE_CREATION_THROTTLE_RATE_PER_SEC * (VM_PAGE_CREATION_THROTTLE_PERIOD_SECS - 1);
			}
			VM_PAGEOUT_DEBUG(vm_page_throttle_count, 1);

			thread->t_page_creation_throttled = 1;

			if (VM_CONFIG_COMPRESSOR_IS_PRESENT && HARD_THROTTLE_LIMIT_REACHED()) {
#if (DEVELOPMENT || DEBUG)
				thread->t_page_creation_throttled_hard++;
				OSAddAtomic(1, &vm_page_creation_throttled_hard);
#endif /* DEVELOPMENT || DEBUG */
				return (HARD_THROTTLE_DELAY);
			} else {
#if (DEVELOPMENT || DEBUG)
				thread->t_page_creation_throttled_soft++;
				OSAddAtomic(1, &vm_page_creation_throttled_soft);
#endif /* DEVELOPMENT || DEBUG */
				return (SOFT_THROTTLE_DELAY);
			}
		}
		thread->t_page_creation_time = tv_sec;
		thread->t_page_creation_count = 0;
	}
no_throttle:
	thread->t_page_creation_count++;

	return (0);
}