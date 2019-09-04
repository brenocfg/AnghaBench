#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zone_t ;
typedef  scalar_t__ vm_size_t ;
struct TYPE_2__ {scalar_t__ kzc_size; } ;

/* Variables and functions */
 int MAX_K_ZONE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * k_zone ; 
 TYPE_1__* k_zone_config ; 
 scalar_t__ kalloc_max ; 
 scalar_t__ kalloc_max_prerounded ; 

__attribute__((used)) static __inline zone_t
get_zone_search(vm_size_t size, int zindex)
{
	assert(size < kalloc_max_prerounded);

	while ((vm_size_t)k_zone_config[zindex].kzc_size < size)
		zindex++;

	assert(zindex < MAX_K_ZONE &&
	    (vm_size_t)k_zone_config[zindex].kzc_size < kalloc_max);

	return (k_zone[zindex]);
}