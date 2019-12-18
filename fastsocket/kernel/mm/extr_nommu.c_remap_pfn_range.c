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
struct vm_area_struct {int vm_start; int vm_pgoff; } ;
typedef  int /*<<< orphan*/  pgprot_t ;

/* Variables and functions */
 int PAGE_SHIFT ; 

int remap_pfn_range(struct vm_area_struct *vma, unsigned long from,
		unsigned long to, unsigned long size, pgprot_t prot)
{
	vma->vm_start = vma->vm_pgoff << PAGE_SHIFT;
	return 0;
}