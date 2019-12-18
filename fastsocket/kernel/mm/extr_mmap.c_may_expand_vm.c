#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mm_struct {unsigned long total_vm; } ;
struct TYPE_6__ {TYPE_2__* signal; } ;
struct TYPE_5__ {TYPE_1__* rlim; } ;
struct TYPE_4__ {unsigned long rlim_cur; } ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 size_t RLIMIT_AS ; 
 TYPE_3__* current ; 

int may_expand_vm(struct mm_struct *mm, unsigned long npages)
{
	unsigned long cur = mm->total_vm;	/* pages */
	unsigned long lim;

	lim = current->signal->rlim[RLIMIT_AS].rlim_cur >> PAGE_SHIFT;

	if (cur + npages > lim)
		return 0;
	return 1;
}