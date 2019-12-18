#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* zone_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  scalar_t__ uint32_t ;
struct zcc_magazine {scalar_t__ zcc_magazine_index; scalar_t__ zcc_magazine_capacity; } ;
struct TYPE_7__ {int /*<<< orphan*/  elem_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASAN_HEAP_FREED ; 
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  kasan_poison_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_zone (TYPE_1__*) ; 
 int /*<<< orphan*/  unlock_zone (TYPE_1__*) ; 
 void* zalloc_attempt (TYPE_1__*) ; 
 int /*<<< orphan*/  zcache_canary_add (TYPE_1__*,void*) ; 
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