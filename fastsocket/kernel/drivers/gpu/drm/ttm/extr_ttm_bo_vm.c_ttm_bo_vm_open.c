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
struct vm_area_struct {scalar_t__ vm_private_data; } ;
struct ttm_buffer_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ttm_bo_reference (struct ttm_buffer_object*) ; 

__attribute__((used)) static void ttm_bo_vm_open(struct vm_area_struct *vma)
{
	struct ttm_buffer_object *bo =
	    (struct ttm_buffer_object *)vma->vm_private_data;

	(void)ttm_bo_reference(bo);
}