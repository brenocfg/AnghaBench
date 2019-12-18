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
struct TYPE_3__ {int flags; } ;
typedef  TYPE_1__ boot_args ;
struct TYPE_4__ {scalar_t__ bootArgs; } ;

/* Variables and functions */
 TYPE_2__ PE_state ; 
 int csr_allow_all ; 
 int kBootArgsFlagCSRBoot ; 

void
csr_init(void)
{
	boot_args *args = (boot_args *)PE_state.bootArgs;
	if (args->flags & kBootArgsFlagCSRBoot) {
		/* special booter; allow everything */
		csr_allow_all = 1;
	}
}