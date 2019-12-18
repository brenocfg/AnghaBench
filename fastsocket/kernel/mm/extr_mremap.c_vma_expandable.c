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
struct vm_area_struct {unsigned long vm_end; scalar_t__ vm_start; TYPE_1__* vm_next; } ;
struct TYPE_2__ {unsigned long vm_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAP_FIXED ; 
 int PAGE_MASK ; 
 int get_unmapped_area (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vma_expandable(struct vm_area_struct *vma, unsigned long delta)
{
	unsigned long end = vma->vm_end + delta;
	if (end < vma->vm_end) /* overflow */
		return 0;
	if (vma->vm_next && vma->vm_next->vm_start < end) /* intersection */
		return 0;
	if (get_unmapped_area(NULL, vma->vm_start, end - vma->vm_start,
			      0, MAP_FIXED) & ~PAGE_MASK)
		return 0;
	return 1;
}