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
struct TYPE_3__ {int /*<<< orphan*/  sc_size; scalar_t__ sc_buffer; } ;
typedef  TYPE_1__ stackshot_config_t ;

/* Variables and functions */

int
stackshot_config_set_size_hint(stackshot_config_t *stackshot_config, uint32_t suggested_size)
{
	if (stackshot_config == NULL || (void *)stackshot_config->sc_buffer != NULL) {
		return -1;
	}

	stackshot_config->sc_size = suggested_size;

	return 0;
}