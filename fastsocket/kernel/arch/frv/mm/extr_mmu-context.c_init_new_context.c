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
struct task_struct {int dummy; } ;
struct TYPE_2__ {int itlb_cached_pge; int dtlb_cached_pge; int /*<<< orphan*/  id_link; } ;
struct mm_struct {TYPE_1__ context; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

int init_new_context(struct task_struct *tsk, struct mm_struct *mm)
{
	memset(&mm->context, 0, sizeof(mm->context));
	INIT_LIST_HEAD(&mm->context.id_link);
	mm->context.itlb_cached_pge = 0xffffffffUL;
	mm->context.dtlb_cached_pge = 0xffffffffUL;

	return 0;
}