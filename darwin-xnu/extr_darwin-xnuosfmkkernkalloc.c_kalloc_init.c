#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_size_t ;
typedef  scalar_t__ vm_offset_t ;
struct TYPE_5__ {int /*<<< orphan*/  vmkf_permanent; } ;
typedef  TYPE_1__ vm_map_kernel_flags_t ;
typedef  scalar_t__ kern_return_t ;
typedef  scalar_t__ int8_t ;
struct TYPE_6__ {scalar_t__ kzc_size; int /*<<< orphan*/  kzc_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ KALLOC_MAP_SIZE_MIN ; 
 scalar_t__ KALLOC_MINALIGN ; 
 scalar_t__ KERN_SUCCESS ; 
 int KiB (int) ; 
 int /*<<< orphan*/  LCK_ATTR_NULL ; 
 int /*<<< orphan*/  LCK_GRP_ATTR_NULL ; 
 int MAX_K_ZONE ; 
 int N_K_ZDLUT ; 
 int /*<<< orphan*/  OSMalloc_init () ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VM_FLAGS_ANYWHERE ; 
 int /*<<< orphan*/  VM_KERN_MEMORY_KALLOC ; 
 TYPE_1__ VM_MAP_KERNEL_FLAGS_NONE ; 
 int /*<<< orphan*/  Z_CALLERACCT ; 
 int /*<<< orphan*/  Z_KASAN_QUARANTINE ; 
 int /*<<< orphan*/  assert (int) ; 
 int k_zindex_start ; 
 int /*<<< orphan*/ * k_zone ; 
 TYPE_3__* k_zone_config ; 
 scalar_t__* k_zone_dlut ; 
 int kalloc_kernmap_size ; 
 int kalloc_largest_allocated ; 
 int /*<<< orphan*/  kalloc_lck_grp ; 
 int /*<<< orphan*/  kalloc_lock ; 
 int /*<<< orphan*/  kalloc_map ; 
 scalar_t__ kalloc_map_max ; 
 scalar_t__ kalloc_map_min ; 
 int kalloc_max ; 
 int kalloc_max_prerounded ; 
 int /*<<< orphan*/  kernel_map ; 
 scalar_t__ kmem_suballoc (int /*<<< orphan*/ ,scalar_t__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_grp_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int sane_size ; 
 int /*<<< orphan*/  zinit (scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zone_change (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
kalloc_init(
	void)
{
	kern_return_t retval;
	vm_offset_t min;
	vm_size_t size, kalloc_map_size;
	vm_map_kernel_flags_t vmk_flags;

	/* 
	 * Scale the kalloc_map_size to physical memory size: stay below 
	 * 1/8th the total zone map size, or 128 MB (for a 32-bit kernel).
	 */
	kalloc_map_size = (vm_size_t)(sane_size >> 5);
#if !__LP64__
	if (kalloc_map_size > KALLOC_MAP_SIZE_MAX)
		kalloc_map_size = KALLOC_MAP_SIZE_MAX;
#endif /* !__LP64__ */
	if (kalloc_map_size < KALLOC_MAP_SIZE_MIN)
		kalloc_map_size = KALLOC_MAP_SIZE_MIN;

	vmk_flags = VM_MAP_KERNEL_FLAGS_NONE;
	vmk_flags.vmkf_permanent = TRUE;

	retval = kmem_suballoc(kernel_map, &min, kalloc_map_size,
			       FALSE,
			       (VM_FLAGS_ANYWHERE),
			       vmk_flags,
			       VM_KERN_MEMORY_KALLOC,
			       &kalloc_map);

	if (retval != KERN_SUCCESS)
		panic("kalloc_init: kmem_suballoc failed");

	kalloc_map_min = min;
	kalloc_map_max = min + kalloc_map_size - 1;

	/*
	 * Create zones up to a least 4 pages because small page-multiples are
	 * common allocations.  Also ensure that zones up to size 16KB bytes exist.
	 * This is desirable because messages are allocated with kalloc(), and
	 * messages up through size 8192 are common.
	 */
	kalloc_max = PAGE_SIZE << 2;
	if (kalloc_max < KiB(16)) {
	    kalloc_max = KiB(16);
	}
	assert(kalloc_max <= KiB(64)); /* assumption made in size arrays */

	kalloc_max_prerounded = kalloc_max / 2 + 1;
	/* allocations larger than 16 times kalloc_max go directly to kernel map */
	kalloc_kernmap_size = (kalloc_max * 16) + 1;
	kalloc_largest_allocated = kalloc_kernmap_size;

	/*
	 * Allocate a zone for each size we are going to handle.
	 */
	for (int i = 0; i < MAX_K_ZONE && (size = k_zone_config[i].kzc_size) < kalloc_max; i++) {
		k_zone[i] = zinit(size, size, size, k_zone_config[i].kzc_name);

		/*
		 * Don't charge the caller for the allocation, as we aren't sure how
		 * the memory will be handled.
		 */
		zone_change(k_zone[i], Z_CALLERACCT, FALSE);
#if VM_MAX_TAG_ZONES
		if (zone_tagging_on) zone_change(k_zone[i], Z_TAGS_ENABLED, TRUE);
#endif
		zone_change(k_zone[i], Z_KASAN_QUARANTINE, FALSE);
	}

	/*
	 * Build the Direct LookUp Table for small allocations
	 */
	size = 0;
	for (int i = 0; i <= N_K_ZDLUT; i++, size += KALLOC_MINALIGN) {
		int zindex = 0;

		while ((vm_size_t)k_zone_config[zindex].kzc_size < size)
			zindex++;

		if (i == N_K_ZDLUT) {
			k_zindex_start = zindex;
			break;
		}
		k_zone_dlut[i] = (int8_t)zindex;
	}

#ifdef KALLOC_DEBUG
	printf("kalloc_init: k_zindex_start %d\n", k_zindex_start);

	/*
	 * Do a quick synthesis to see how well/badly we can
	 * find-a-zone for a given size.
	 * Useful when debugging/tweaking the array of zone sizes.
	 * Cache misses probably more critical than compare-branches!
	 */
	for (int i = 0; i < MAX_K_ZONE; i++) {
		vm_size_t testsize = (vm_size_t)k_zone_config[i].kzc_size - 1;
		int compare = 0;
		int zindex;

		if (testsize < MAX_SIZE_ZDLUT) {
			compare += 1;	/* 'if' (T) */

			long dindex = INDEX_ZDLUT(testsize);
			zindex = (int)k_zone_dlut[dindex];

		} else if (testsize < kalloc_max_prerounded) {

			compare += 2;	/* 'if' (F), 'if' (T) */

			zindex = k_zindex_start;
			while ((vm_size_t)k_zone_config[zindex].kzc_size < testsize) {
				zindex++;
				compare++;	/* 'while' (T) */
			}
			compare++;	/* 'while' (F) */
		} else
			break;	/* not zone-backed */

		zone_t z = k_zone[zindex];
		printf("kalloc_init: req size %4lu: %11s took %d compare%s\n",
		    (unsigned long)testsize, z->zone_name, compare,
		    compare == 1 ? "" : "s");
	}
#endif

	lck_grp_init(&kalloc_lck_grp, "kalloc.large", LCK_GRP_ATTR_NULL);
	lck_mtx_init(&kalloc_lock, &kalloc_lck_grp, LCK_ATTR_NULL);
	OSMalloc_init();
#ifdef	MUTEX_ZONE
	lck_mtx_zone = zinit(sizeof(struct _lck_mtx_), 1024*256, 4096, "lck_mtx");
#endif
}