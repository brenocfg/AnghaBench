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
struct ttm_placement {scalar_t__ fpfn; scalar_t__ lpfn; } ;
struct TYPE_2__ {scalar_t__ num_pages; } ;
struct ttm_buffer_object {TYPE_1__ mem; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 

int ttm_bo_check_placement(struct ttm_buffer_object *bo,
				struct ttm_placement *placement)
{
	BUG_ON((placement->fpfn || placement->lpfn) &&
	       (bo->mem.num_pages > (placement->lpfn - placement->fpfn)));

	return 0;
}