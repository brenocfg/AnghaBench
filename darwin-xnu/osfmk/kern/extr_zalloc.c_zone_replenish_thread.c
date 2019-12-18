#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_8__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* zone_t ;
typedef  int vm_size_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  scalar_t__ kern_return_t ;
typedef  TYPE_1__* event_t ;
struct TYPE_10__ {int /*<<< orphan*/  options; } ;
struct TYPE_9__ {int zone_valid; int prio_refill_watermark; int cur_size; int count; int elem_size; scalar_t__ doing_alloc_without_vm_priv; scalar_t__ doing_alloc_with_vm_priv; scalar_t__ async_prio_refill; int /*<<< orphan*/  zone_replenish_thread; scalar_t__ zone_replenishing; scalar_t__ noencrypt; int /*<<< orphan*/  alloc_size; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ KERN_NO_SPACE ; 
 scalar_t__ KERN_RESOURCE_SHORTAGE ; 
 scalar_t__ KERN_SUCCESS ; 
 int KMA_KOBJECT ; 
 int KMA_NOENCRYPT ; 
 int KMA_NOPAGEWAIT ; 
 int NSEC_PER_USEC ; 
 int /*<<< orphan*/  THREAD_CONTINUE_NULL ; 
 int /*<<< orphan*/  THREAD_UNINT ; 
 int /*<<< orphan*/  TH_OPT_VMPRIV ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  VM_KERN_MEMORY_ZONE ; 
 int /*<<< orphan*/  VM_PAGE_WAIT () ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  assert_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_wait_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 TYPE_8__* current_thread () ; 
 scalar_t__ is_zone_map_nearing_exhaustion () ; 
 int /*<<< orphan*/  kernel_map ; 
 scalar_t__ kernel_memory_allocate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_zone (TYPE_1__*) ; 
 int /*<<< orphan*/  round_page (int) ; 
 int /*<<< orphan*/  thread_block (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_wakeup (TYPE_1__*) ; 
 int /*<<< orphan*/  unlock_zone (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_pageout_garbage_collect ; 
 scalar_t__ vm_pool_low () ; 
 int /*<<< orphan*/  zcram (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zone_map ; 
 int /*<<< orphan*/  zone_replenish_loops ; 
 int /*<<< orphan*/  zone_replenish_wakeups ; 

__attribute__((used)) __attribute__((noreturn))
static void
zone_replenish_thread(zone_t z)
{
	vm_size_t free_size;
	current_thread()->options |= TH_OPT_VMPRIV;

	for (;;) {
		lock_zone(z);
		assert(z->zone_valid);
		z->zone_replenishing = TRUE;
		assert(z->prio_refill_watermark != 0);
		while ((free_size = (z->cur_size - (z->count * z->elem_size))) < (z->prio_refill_watermark * z->elem_size)) {
			assert(z->doing_alloc_without_vm_priv == FALSE);
			assert(z->doing_alloc_with_vm_priv == FALSE);
			assert(z->async_prio_refill == TRUE);

			unlock_zone(z);
			int	zflags = KMA_KOBJECT|KMA_NOPAGEWAIT;
			vm_offset_t space, alloc_size;
			kern_return_t kr;
				
			if (vm_pool_low())
				alloc_size = round_page(z->elem_size);
			else
				alloc_size = z->alloc_size;
				
			if (z->noencrypt)
				zflags |= KMA_NOENCRYPT;
				
			/* Trigger jetsams via the vm_pageout_garbage_collect thread if we're running out of zone memory */
			if (is_zone_map_nearing_exhaustion()) {
				thread_wakeup((event_t) &vm_pageout_garbage_collect);
			}

			kr = kernel_memory_allocate(zone_map, &space, alloc_size, 0, zflags, VM_KERN_MEMORY_ZONE);

			if (kr == KERN_SUCCESS) {
				zcram(z, space, alloc_size);
			} else if (kr == KERN_RESOURCE_SHORTAGE) {
				VM_PAGE_WAIT();
			} else if (kr == KERN_NO_SPACE) {
				kr = kernel_memory_allocate(kernel_map, &space, alloc_size, 0, zflags, VM_KERN_MEMORY_ZONE);
				if (kr == KERN_SUCCESS) {
					zcram(z, space, alloc_size);
				} else {
					assert_wait_timeout(&z->zone_replenish_thread, THREAD_UNINT, 1, 100 * NSEC_PER_USEC);
					thread_block(THREAD_CONTINUE_NULL);
				}
			}

			lock_zone(z);
			assert(z->zone_valid);
			zone_replenish_loops++;
		}

		z->zone_replenishing = FALSE;
		/* Signal any potential throttled consumers, terminating
		 * their timer-bounded waits.
		 */
		thread_wakeup(z);

		assert_wait(&z->zone_replenish_thread, THREAD_UNINT);
		unlock_zone(z);
		thread_block(THREAD_CONTINUE_NULL);
		zone_replenish_wakeups++;
	}
}