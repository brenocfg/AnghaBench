#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  task_t ;
typedef  TYPE_1__* proc_t ;
struct TYPE_3__ {int /*<<< orphan*/  p_flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSBitOrAtomic (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  P_DEPENDENCY_CAPABLE ; 
 TYPE_1__* get_bsdtask_info (int /*<<< orphan*/ ) ; 

void
bsd_set_dependency_capable(task_t task)
{
    proc_t p = get_bsdtask_info(task);

    if (p) {
	OSBitOrAtomic(P_DEPENDENCY_CAPABLE, &p->p_flag);
    }
}