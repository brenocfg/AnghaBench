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
struct TYPE_3__ {scalar_t__ sc_size; scalar_t__ sc_buffer; } ;
typedef  TYPE_1__ stackshot_config_t ;
typedef  int /*<<< orphan*/  mach_vm_size_t ;
typedef  int /*<<< orphan*/  mach_vm_offset_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  mach_task_self () ; 
 int /*<<< orphan*/  mach_vm_deallocate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
stackshot_config_dealloc_buffer(stackshot_config_t *stackshot_config)
{
	stackshot_config_t *s_config;

	if (stackshot_config == NULL) {
		return EINVAL;
	}
	s_config = (stackshot_config_t *) stackshot_config;

	if (s_config->sc_size && s_config->sc_buffer) {
		mach_vm_deallocate(mach_task_self(), (mach_vm_offset_t)s_config->sc_buffer, (mach_vm_size_t)s_config->sc_size);
	}

	s_config->sc_buffer = 0;
	s_config->sc_size = 0;

	return 0;
}