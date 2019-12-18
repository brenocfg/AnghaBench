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
struct vm_area_struct {int dummy; } ;
struct mm_struct {int /*<<< orphan*/  mmap_sem; } ;
struct gru_thread_state {int /*<<< orphan*/  ts_ctxlock; } ;
struct TYPE_2__ {struct mm_struct* mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  TSID (unsigned long,struct vm_area_struct*) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 struct gru_thread_state* gru_find_thread_state (struct vm_area_struct*,int /*<<< orphan*/ ) ; 
 struct vm_area_struct* gru_find_vma (unsigned long) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct gru_thread_state *gru_find_lock_gts(unsigned long vaddr)
{
	struct mm_struct *mm = current->mm;
	struct vm_area_struct *vma;
	struct gru_thread_state *gts = NULL;

	down_read(&mm->mmap_sem);
	vma = gru_find_vma(vaddr);
	if (vma)
		gts = gru_find_thread_state(vma, TSID(vaddr, vma));
	if (gts)
		mutex_lock(&gts->ts_ctxlock);
	else
		up_read(&mm->mmap_sem);
	return gts;
}