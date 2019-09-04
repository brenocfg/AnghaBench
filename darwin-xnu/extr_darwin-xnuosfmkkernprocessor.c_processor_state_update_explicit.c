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
typedef  int /*<<< orphan*/  sfi_class_id_t ;
typedef  int /*<<< orphan*/  pset_cluster_type_t ;
typedef  TYPE_1__* processor_t ;
typedef  int /*<<< orphan*/  perfcontrol_class_t ;
struct TYPE_3__ {int current_pri; int /*<<< orphan*/  current_perfctl_class; int /*<<< orphan*/  current_recommended_pset_type; int /*<<< orphan*/  current_sfi_class; } ;

/* Variables and functions */

void
processor_state_update_explicit(processor_t processor, int pri, sfi_class_id_t sfi_class, 
	pset_cluster_type_t pset_type, perfcontrol_class_t perfctl_class)
{
    processor->current_pri = pri;
    processor->current_sfi_class = sfi_class;
    processor->current_recommended_pset_type = pset_type;
    processor->current_perfctl_class = perfctl_class;
}