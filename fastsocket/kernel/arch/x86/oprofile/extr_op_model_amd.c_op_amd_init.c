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
struct oprofile_operations {int /*<<< orphan*/  create_files; } ;
struct TYPE_4__ {int x86; } ;
struct TYPE_3__ {int /*<<< orphan*/  num_virt_counters; void* num_controls; void* num_counters; } ;

/* Variables and functions */
 void* NUM_COUNTERS ; 
 void* NUM_COUNTERS_F15H ; 
 int /*<<< orphan*/  NUM_VIRT_COUNTERS ; 
 TYPE_2__ boot_cpu_data ; 
 int /*<<< orphan*/  create_arch_files ; 
 int /*<<< orphan*/  init_ibs () ; 
 int /*<<< orphan*/  max (void*,int /*<<< orphan*/ ) ; 
 void* num_counters ; 
 TYPE_1__ op_amd_spec ; 
 int /*<<< orphan*/  setup_ibs_files ; 

__attribute__((used)) static int op_amd_init(struct oprofile_operations *ops)
{
	init_ibs();
	create_arch_files = ops->create_files;
	ops->create_files = setup_ibs_files;

	if (boot_cpu_data.x86 == 0x15) {
		num_counters = NUM_COUNTERS_F15H;
	} else {
		num_counters = NUM_COUNTERS;
	}

	op_amd_spec.num_counters = num_counters;
	op_amd_spec.num_controls = num_counters;
	op_amd_spec.num_virt_counters = max(num_counters, NUM_VIRT_COUNTERS);

	return 0;
}