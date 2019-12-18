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
struct TYPE_2__ {int /*<<< orphan*/  user_cs; scalar_t__ exec_limit; } ;
struct mm_struct {TYPE_1__ context; } ;

/* Variables and functions */
 int /*<<< orphan*/  set_user_cs (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void arch_flush_exec_range(struct mm_struct *mm)
{
	mm->context.exec_limit = 0;
	set_user_cs(&mm->context.user_cs, 0);
}