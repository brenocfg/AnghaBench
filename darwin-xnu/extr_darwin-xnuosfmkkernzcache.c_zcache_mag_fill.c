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
typedef  int /*<<< orphan*/  zone_t ;
typedef  scalar_t__ uint32_t ;
struct zcc_magazine {scalar_t__ zcc_magazine_index; scalar_t__ zcc_magazine_capacity; } ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  lock_zone (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_zone (int /*<<< orphan*/ ) ; 
 void* zalloc_attempt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zcache_canary_add (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  zcache_mag_push (struct zcc_magazine*,void*) ; 

bool zcache_mag_fill(zone_t zone, struct zcc_magazine *mag)
{
	assert(mag->zcc_magazine_index == 0);
	void* elem = NULL;
	uint32_t i;
	lock_zone(zone);
	for(i = mag->zcc_magazine_index; i < mag->zcc_magazine_capacity; i ++){
		elem = zalloc_attempt(zone);
		if(elem) {
			zcache_canary_add(zone, elem);
			zcache_mag_push(mag, elem);
#if KASAN_ZALLOC
			kasan_poison_range((vm_offset_t)elem, zone->elem_size, ASAN_HEAP_FREED);
#endif
		} else {
			break;
		}
	}
	unlock_zone(zone);
	if (i == 0){
		return FALSE;
	}
	return TRUE;
}