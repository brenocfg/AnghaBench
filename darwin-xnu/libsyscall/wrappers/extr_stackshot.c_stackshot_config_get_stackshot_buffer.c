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
struct TYPE_3__ {scalar_t__ sc_buffer; } ;
typedef  TYPE_1__ stackshot_config_t ;

/* Variables and functions */

void *
stackshot_config_get_stackshot_buffer(stackshot_config_t *stackshot_config)
{
	stackshot_config_t *s_config;

	if (stackshot_config == NULL) {
		return NULL;
	}
	s_config = (stackshot_config_t *) stackshot_config;

	return ((void *)s_config->sc_buffer);
}