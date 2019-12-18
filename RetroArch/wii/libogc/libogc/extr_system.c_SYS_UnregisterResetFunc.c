#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_7__ {struct TYPE_7__* next; } ;
struct TYPE_6__ {TYPE_2__ node; } ;
typedef  TYPE_1__ sys_resetinfo ;
typedef  TYPE_2__ lwp_node ;
struct TYPE_8__ {TYPE_2__* first; } ;

/* Variables and functions */
 int /*<<< orphan*/  _CPU_ISR_Disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __lwp_queue_extractI (TYPE_2__*) ; 
 TYPE_3__ sys_reset_func_queue ; 

void SYS_UnregisterResetFunc(sys_resetinfo *info) {
	u32 level;
	lwp_node *n;

	_CPU_ISR_Disable(level);
	for (n = sys_reset_func_queue.first; n->next; n = n->next) {
		if (n == &info->node) {
			__lwp_queue_extractI(n);
			break;
		}
	}
	_CPU_ISR_Restore(level);
}