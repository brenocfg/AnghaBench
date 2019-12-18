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
struct TYPE_2__ {int context; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  flush_cache_all () ; 
 int /*<<< orphan*/  flush_user_dcache_range (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  flush_user_icache_range (unsigned long,unsigned long) ; 
 int mfsp (int) ; 

void flush_cache_range(struct vm_area_struct *vma,
		unsigned long start, unsigned long end)
{
	int sr3;

	BUG_ON(!vma->vm_mm->context);

	sr3 = mfsp(3);
	if (vma->vm_mm->context == sr3) {
		flush_user_dcache_range(start,end);
		flush_user_icache_range(start,end);
	} else {
		flush_cache_all();
	}
}