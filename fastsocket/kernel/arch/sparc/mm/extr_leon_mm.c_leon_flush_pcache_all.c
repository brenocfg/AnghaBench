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

/* Variables and functions */
 int VM_EXEC ; 
 int /*<<< orphan*/  leon_flush_dcache_all () ; 
 int /*<<< orphan*/  leon_flush_icache_all () ; 

void leon_flush_pcache_all(struct vm_area_struct *vma, unsigned long page)
{
	if (vma->vm_flags & VM_EXEC)
		leon_flush_icache_all();
	leon_flush_dcache_all();
}