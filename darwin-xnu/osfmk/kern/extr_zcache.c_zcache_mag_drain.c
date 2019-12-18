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
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  size_t uint32_t ;
struct zcc_magazine {size_t zcc_magazine_index; size_t zcc_magazine_capacity; scalar_t__* zcc_elements; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  lock_zone (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_zone (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zcache_canary_validate (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  zfree_direct (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void zcache_mag_drain(zone_t zone, struct zcc_magazine *mag)
{
	assert(mag->zcc_magazine_index == mag->zcc_magazine_capacity);
	lock_zone(zone);
	while(mag->zcc_magazine_index > 0){
		uint32_t index = --mag->zcc_magazine_index;
		zcache_canary_validate(zone, mag->zcc_elements[index]);
		zfree_direct(zone,(vm_offset_t)mag->zcc_elements[index]);
		mag->zcc_elements[mag->zcc_magazine_index] = 0;
	}
	unlock_zone(zone);
}