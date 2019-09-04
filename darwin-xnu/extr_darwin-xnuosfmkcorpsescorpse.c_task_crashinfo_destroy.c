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
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  TYPE_1__* kcdata_descriptor_t ;
struct TYPE_4__ {int kcd_user_flags; } ;

/* Variables and functions */
 int CORPSE_CRASHINFO_HAS_REF ; 
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  kcdata_memory_destroy (TYPE_1__*) ; 
 int /*<<< orphan*/  task_crashinfo_release_ref (int) ; 

kern_return_t
task_crashinfo_destroy(kcdata_descriptor_t data)
{
	if (!data) {
		return KERN_INVALID_ARGUMENT;
	}
	if (data->kcd_user_flags & CORPSE_CRASHINFO_HAS_REF) {
		task_crashinfo_release_ref(data->kcd_user_flags);
	}
	return kcdata_memory_destroy(data);
}