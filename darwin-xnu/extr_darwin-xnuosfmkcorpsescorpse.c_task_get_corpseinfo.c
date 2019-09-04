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
typedef  TYPE_1__* task_t ;
typedef  int /*<<< orphan*/ * kcdata_descriptor_t ;
struct TYPE_3__ {int /*<<< orphan*/ * corpse_info; } ;

/* Variables and functions */

kcdata_descriptor_t task_get_corpseinfo(task_t task)
{
	kcdata_descriptor_t retval = NULL;
	if (task != NULL){
		retval = task->corpse_info;
	}
	return retval;
}