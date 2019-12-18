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
struct task_struct {int dummy; } ;
struct page {int dummy; } ;
struct mm_struct {int dummy; } ;

/* Variables and functions */
 int FOLL_FORCE ; 
 int FOLL_WRITE ; 
 int __get_user_pages (struct task_struct*,struct mm_struct*,unsigned long,int,int,struct page**,struct vm_area_struct**) ; 

int get_user_pages(struct task_struct *tsk, struct mm_struct *mm,
	unsigned long start, int nr_pages, int write, int force,
	struct page **pages, struct vm_area_struct **vmas)
{
	int flags = 0;

	if (write)
		flags |= FOLL_WRITE;
	if (force)
		flags |= FOLL_FORCE;

	return __get_user_pages(tsk, mm, start, nr_pages, flags, pages, vmas);
}