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
struct TYPE_3__ {scalar_t__ sc_buffer; uintptr_t sc_out_buffer_addr; uintptr_t sc_out_size_addr; scalar_t__ sc_size; } ;
typedef  TYPE_1__ stackshot_config_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  STACKSHOT_CONFIG_TYPE ; 
 int __stack_snapshot_with_config (int /*<<< orphan*/ ,uintptr_t,int) ; 
 int errno ; 

int
stackshot_capture_with_config(stackshot_config_t *stackshot_config)
{
	int ret;
	stackshot_config_t *s_config;

	if (stackshot_config == NULL) {
		return EINVAL;
	}

	s_config = (stackshot_config_t *) stackshot_config;
	if (s_config->sc_buffer != 0)  {
		return EINVAL;
	}

	s_config->sc_out_buffer_addr = (uintptr_t)&s_config->sc_buffer;
	s_config->sc_out_size_addr = (uintptr_t)&s_config->sc_size;
	ret = __stack_snapshot_with_config(STACKSHOT_CONFIG_TYPE, (uintptr_t)s_config, sizeof(stackshot_config_t));
	
	if (ret != 0) {
		ret = errno;
		s_config->sc_buffer = 0;
		s_config->sc_size = 0;
	}

	return ret;
}