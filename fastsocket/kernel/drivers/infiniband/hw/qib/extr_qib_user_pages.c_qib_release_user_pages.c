#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct TYPE_4__ {TYPE_1__* mm; } ;
struct TYPE_3__ {size_t locked_vm; int /*<<< orphan*/  mmap_sem; } ;

/* Variables and functions */
 int /*<<< orphan*/  __qib_release_user_pages (struct page**,size_t,int) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void qib_release_user_pages(struct page **p, size_t num_pages)
{
	if (current->mm) /* during close after signal, mm can be NULL */
		down_write(&current->mm->mmap_sem);

	__qib_release_user_pages(p, num_pages, 1);

	if (current->mm) {
		current->mm->locked_vm -= num_pages;
		up_write(&current->mm->mmap_sem);
	}
}