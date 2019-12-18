#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {void* current_size; } ;
struct TYPE_6__ {unsigned int size; } ;
struct TYPE_5__ {unsigned int gtt_mappable_entries; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
 unsigned int MB (int) ; 
 unsigned int PAGE_SHIFT ; 
 TYPE_3__* agp_bridge ; 
 TYPE_2__* intel_fake_agp_sizes ; 
 TYPE_1__ intel_private ; 

__attribute__((used)) static int intel_fake_agp_fetch_size(void)
{
	int num_sizes = ARRAY_SIZE(intel_fake_agp_sizes);
	unsigned int aper_size;
	int i;

	aper_size = (intel_private.gtt_mappable_entries << PAGE_SHIFT) / MB(1);

	for (i = 0; i < num_sizes; i++) {
		if (aper_size == intel_fake_agp_sizes[i].size) {
			agp_bridge->current_size =
				(void *) (intel_fake_agp_sizes + i);
			return aper_size;
		}
	}

	return 0;
}