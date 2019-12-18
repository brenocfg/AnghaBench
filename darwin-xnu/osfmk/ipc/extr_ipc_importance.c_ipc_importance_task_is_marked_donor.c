#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ipc_importance_task_t ;
typedef  int boolean_t ;
struct TYPE_4__ {scalar_t__ iit_donor; } ;

/* Variables and functions */
 int FALSE ; 
 TYPE_1__* IIT_NULL ; 

boolean_t
ipc_importance_task_is_marked_donor(ipc_importance_task_t task_imp)
{
	if (IIT_NULL == task_imp) {
  		return FALSE;
	}
	return (0 != task_imp->iit_donor);
}