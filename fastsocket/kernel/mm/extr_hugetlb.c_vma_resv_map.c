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
struct vm_area_struct {int vm_flags; } ;
struct resv_map {int dummy; } ;

/* Variables and functions */
 int HPAGE_RESV_MASK ; 
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 int VM_MAYSHARE ; 
 int get_vma_private_data (struct vm_area_struct*) ; 
 int /*<<< orphan*/  is_vm_hugetlb_page (struct vm_area_struct*) ; 

__attribute__((used)) static struct resv_map *vma_resv_map(struct vm_area_struct *vma)
{
	VM_BUG_ON(!is_vm_hugetlb_page(vma));
	if (!(vma->vm_flags & VM_MAYSHARE))
		return (struct resv_map *)(get_vma_private_data(vma) &
							~HPAGE_RESV_MASK);
	return NULL;
}