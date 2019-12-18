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
struct vm_area_struct {TYPE_1__* vm_mm; } ;
struct TYPE_2__ {int /*<<< orphan*/  context; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  __flush_cache_page (struct vm_area_struct*,unsigned long) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  translation_exists (struct vm_area_struct*,unsigned long,unsigned long) ; 

void
flush_cache_page(struct vm_area_struct *vma, unsigned long vmaddr, unsigned long pfn)
{
	BUG_ON(!vma->vm_mm->context);

	if (likely(translation_exists(vma, vmaddr, pfn)))
		__flush_cache_page(vma, vmaddr);

}