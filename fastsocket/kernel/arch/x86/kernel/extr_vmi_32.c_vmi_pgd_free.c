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
struct mm_struct {int dummy; } ;
typedef  int /*<<< orphan*/  pgd_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* release_page ) (unsigned long,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  VMI_PAGE_L2 ; 
 unsigned long __pa (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (unsigned long,int /*<<< orphan*/ ) ; 
 TYPE_1__ vmi_ops ; 

__attribute__((used)) static void vmi_pgd_free(struct mm_struct *mm, pgd_t *pgd)
{
	unsigned long pfn = __pa(pgd) >> PAGE_SHIFT;

	vmi_ops.release_page(pfn, VMI_PAGE_L2);
}