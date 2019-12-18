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
struct TYPE_3__ {unsigned long exec_limit; int /*<<< orphan*/  user_cs; } ;
struct mm_struct {TYPE_1__ context; } ;
struct TYPE_4__ {struct mm_struct* mm; } ;

/* Variables and functions */
 TYPE_2__* current ; 
 int get_cpu () ; 
 int /*<<< orphan*/  load_user_cs_desc (int,struct mm_struct*) ; 
 int /*<<< orphan*/  put_cpu () ; 
 int /*<<< orphan*/  set_user_cs (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void modify_cs(struct mm_struct *mm, unsigned long limit)
{
	mm->context.exec_limit = limit;
	set_user_cs(&mm->context.user_cs, limit);
	if (mm == current->mm) {
		int cpu;

		cpu = get_cpu();
		load_user_cs_desc(cpu, mm);
		put_cpu();
	}
}