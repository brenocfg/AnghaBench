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
typedef  TYPE_1__* processor_t ;
struct TYPE_3__ {int /*<<< orphan*/  current_perfctl_class; int /*<<< orphan*/  current_recommended_pset_type; int /*<<< orphan*/  current_sfi_class; int /*<<< orphan*/  current_pri; } ;

/* Variables and functions */
 int /*<<< orphan*/  IDLEPRI ; 
 int /*<<< orphan*/  PERFCONTROL_CLASS_IDLE ; 
 int /*<<< orphan*/  PSET_SMP ; 
 int /*<<< orphan*/  SFI_CLASS_KERNEL ; 

void
processor_state_update_idle(processor_t processor)
{
    processor->current_pri = IDLEPRI;
    processor->current_sfi_class = SFI_CLASS_KERNEL;
    processor->current_recommended_pset_type = PSET_SMP;
    processor->current_perfctl_class = PERFCONTROL_CLASS_IDLE;
}