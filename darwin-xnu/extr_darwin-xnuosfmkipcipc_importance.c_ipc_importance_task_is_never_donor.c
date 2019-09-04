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
typedef  scalar_t__ ipc_importance_task_t ;
typedef  int boolean_t ;

/* Variables and functions */
 int FALSE ; 
 scalar_t__ IIT_NULL ; 
 int /*<<< orphan*/  ipc_importance_task_is_marked_donor (scalar_t__) ; 
 int /*<<< orphan*/  ipc_importance_task_is_marked_live_donor (scalar_t__) ; 
 int /*<<< orphan*/  ipc_importance_task_is_marked_receiver (scalar_t__) ; 

boolean_t
ipc_importance_task_is_never_donor(ipc_importance_task_t task_imp)
{
	if (IIT_NULL == task_imp) {
  		return FALSE;
	}
	return (!ipc_importance_task_is_marked_donor(task_imp) &&
		!ipc_importance_task_is_marked_live_donor(task_imp) &&
		!ipc_importance_task_is_marked_receiver(task_imp));
}