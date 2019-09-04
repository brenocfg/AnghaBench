#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_offset_t ;
struct TYPE_5__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ ex_cb_state_t ;
struct TYPE_6__ {int /*<<< orphan*/  refcon; int /*<<< orphan*/  (* cb ) (size_t,int /*<<< orphan*/ ,TYPE_1__*) ;} ;
typedef  TYPE_2__ ex_cb_info_t ;
typedef  size_t ex_cb_class_t ;
typedef  int /*<<< orphan*/  ex_cb_action_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXCB_ACTION_NONE ; 
 size_t EXCB_CLASS_MAX ; 
 TYPE_2__* ex_cb_info ; 
 int /*<<< orphan*/  panic (char*,size_t) ; 
 int /*<<< orphan*/  stub1 (size_t,int /*<<< orphan*/ ,TYPE_1__*) ; 

ex_cb_action_t ex_cb_invoke(
	ex_cb_class_t	cb_class,
	vm_offset_t		far)
{
	ex_cb_info_t *pInfo = &ex_cb_info[cb_class];
	ex_cb_state_t state = {far};

	if (cb_class >= EXCB_CLASS_MAX)
	{
		panic("Invalid exception callback class 0x%x\n", cb_class);
	}

	if (pInfo->cb)
	{
		return pInfo->cb(cb_class, pInfo->refcon, &state);
	}
	return EXCB_ACTION_NONE;
}