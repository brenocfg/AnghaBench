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
struct ttm_buffer_object {int /*<<< orphan*/  list_kref; } ;

/* Variables and functions */
 int /*<<< orphan*/  kref_sub (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttm_bo_ref_bug ; 
 int /*<<< orphan*/  ttm_bo_release_list ; 

void ttm_bo_list_ref_sub(struct ttm_buffer_object *bo, int count,
			 bool never_free)
{
	kref_sub(&bo->list_kref, count,
		 (never_free) ? ttm_bo_ref_bug : ttm_bo_release_list);
}