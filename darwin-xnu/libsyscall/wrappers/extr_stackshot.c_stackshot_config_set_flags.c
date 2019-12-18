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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  sc_flags; } ;
typedef  TYPE_1__ stackshot_config_t ;

/* Variables and functions */
 int EINVAL ; 

int
stackshot_config_set_flags(stackshot_config_t *stackshot_config, uint32_t flags)
{
	stackshot_config_t *s_config;

	if (stackshot_config == NULL) {
		return EINVAL;
	}

	s_config = (stackshot_config_t *) stackshot_config;
	s_config->sc_flags = flags;

	return 0;
}