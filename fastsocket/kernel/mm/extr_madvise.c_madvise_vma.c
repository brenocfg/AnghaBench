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
struct vm_area_struct {int dummy; } ;

/* Variables and functions */
#define  MADV_DONTNEED 130 
#define  MADV_REMOVE 129 
#define  MADV_WILLNEED 128 
 long madvise_behavior (struct vm_area_struct*,struct vm_area_struct**,unsigned long,unsigned long,int) ; 
 long madvise_dontneed (struct vm_area_struct*,struct vm_area_struct**,unsigned long,unsigned long) ; 
 long madvise_remove (struct vm_area_struct*,struct vm_area_struct**,unsigned long,unsigned long) ; 
 long madvise_willneed (struct vm_area_struct*,struct vm_area_struct**,unsigned long,unsigned long) ; 

__attribute__((used)) static long
madvise_vma(struct vm_area_struct *vma, struct vm_area_struct **prev,
		unsigned long start, unsigned long end, int behavior)
{
	switch (behavior) {
	case MADV_REMOVE:
		return madvise_remove(vma, prev, start, end);
	case MADV_WILLNEED:
		return madvise_willneed(vma, prev, start, end);
	case MADV_DONTNEED:
		return madvise_dontneed(vma, prev, start, end);
	default:
		return madvise_behavior(vma, prev, start, end, behavior);
	}
}