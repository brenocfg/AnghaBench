#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ipc_importance_task_t ;
struct TYPE_6__ {int /*<<< orphan*/  iie_task_refs_added; } ;
struct TYPE_5__ {TYPE_3__ iit_elem; } ;

/* Variables and functions */
 TYPE_1__* IIT_NULL ; 
 int /*<<< orphan*/  incr_ref_counter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipc_importance_reference (TYPE_3__*) ; 

void
ipc_importance_task_reference(ipc_importance_task_t task_elem)
{
	if (IIT_NULL == task_elem)
		return;
#if IIE_REF_DEBUG
	incr_ref_counter(task_elem->iit_elem.iie_task_refs_added);
#endif
	ipc_importance_reference(&task_elem->iit_elem);
}