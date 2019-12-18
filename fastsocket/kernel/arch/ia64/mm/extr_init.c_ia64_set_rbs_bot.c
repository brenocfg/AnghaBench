#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  rbs_bot; } ;
struct TYPE_10__ {TYPE_4__* mm; TYPE_3__ thread; TYPE_2__* signal; } ;
struct TYPE_9__ {scalar_t__ start_stack; } ;
struct TYPE_7__ {TYPE_1__* rlim; } ;
struct TYPE_6__ {int rlim_max; } ;

/* Variables and functions */
 unsigned long MAX_USER_STACK_SIZE ; 
 int /*<<< orphan*/  PAGE_ALIGN (scalar_t__) ; 
 size_t RLIMIT_STACK ; 
 TYPE_5__* current ; 

inline void
ia64_set_rbs_bot (void)
{
	unsigned long stack_size = current->signal->rlim[RLIMIT_STACK].rlim_max & -16;

	if (stack_size > MAX_USER_STACK_SIZE)
		stack_size = MAX_USER_STACK_SIZE;
	current->thread.rbs_bot = PAGE_ALIGN(current->mm->start_stack - stack_size);
}