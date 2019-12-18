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
struct TYPE_2__ {int /*<<< orphan*/  (* allocate_page ) (unsigned long,int,unsigned long,unsigned long,unsigned long) ;} ;

/* Variables and functions */
 int VMI_PAGE_CLONE ; 
 int VMI_PAGE_L2 ; 
 int /*<<< orphan*/  stub1 (unsigned long,int,unsigned long,unsigned long,unsigned long) ; 
 TYPE_1__ vmi_ops ; 

__attribute__((used)) static void vmi_allocate_pmd_clone(unsigned long pfn, unsigned long clonepfn, unsigned long start, unsigned long count)
{
	vmi_ops.allocate_page(pfn, VMI_PAGE_L2 | VMI_PAGE_CLONE, clonepfn, start, count);
}