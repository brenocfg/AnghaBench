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
struct TYPE_4__ {int sc_pid; scalar_t__ sc_size; scalar_t__ sc_buffer; scalar_t__ sc_delta_timestamp; scalar_t__ sc_flags; } ;
typedef  TYPE_1__ stackshot_config_t ;

/* Variables and functions */
 TYPE_1__* malloc (int) ; 

stackshot_config_t *
stackshot_config_create(void)
{
	stackshot_config_t *s_config;

	s_config = malloc(sizeof(stackshot_config_t));
	if (s_config == NULL) {
		return NULL;
	}

	s_config->sc_pid = -1;
	s_config->sc_flags = 0;
	s_config->sc_delta_timestamp = 0;
	s_config->sc_buffer = 0;
	s_config->sc_size = 0;

	return s_config;
}