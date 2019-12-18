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
struct agp_memory {scalar_t__ page_count; scalar_t__ num_sg; int /*<<< orphan*/ * sg_list; } ;
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_2__ {scalar_t__ needs_dmar; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_gtt_clear_range (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  intel_gtt_unmap_memory (int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_1__ intel_private ; 

__attribute__((used)) static int intel_fake_agp_remove_entries(struct agp_memory *mem,
					 off_t pg_start, int type)
{
	if (mem->page_count == 0)
		return 0;

	intel_gtt_clear_range(pg_start, mem->page_count);

	if (intel_private.needs_dmar) {
		intel_gtt_unmap_memory(mem->sg_list, mem->num_sg);
		mem->sg_list = NULL;
		mem->num_sg = 0;
	}

	return 0;
}