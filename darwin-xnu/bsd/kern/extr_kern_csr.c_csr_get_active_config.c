#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int csr_config_t ;
struct TYPE_3__ {int flags; int csrActiveConfig; } ;
typedef  TYPE_1__ boot_args ;
struct TYPE_4__ {scalar_t__ bootArgs; } ;

/* Variables and functions */
 int CSR_VALID_FLAGS ; 
 TYPE_2__ PE_state ; 
 int kBootArgsFlagCSRActiveConfig ; 

int
csr_get_active_config(csr_config_t *config)
{
	boot_args *args = (boot_args *)PE_state.bootArgs;
	if (args->flags & kBootArgsFlagCSRActiveConfig) {
		*config = args->csrActiveConfig & CSR_VALID_FLAGS;
	} else {
		*config = 0;
	}

	return 0;
}