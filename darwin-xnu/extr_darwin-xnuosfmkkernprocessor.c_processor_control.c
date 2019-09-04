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
typedef  TYPE_1__* processor_t ;
typedef  int /*<<< orphan*/  processor_info_t ;
typedef  int /*<<< orphan*/  mach_msg_type_number_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_4__ {int /*<<< orphan*/  cpu_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 TYPE_1__* PROCESSOR_NULL ; 
 int /*<<< orphan*/  cpu_control (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

kern_return_t
processor_control(
	processor_t		processor,
	processor_info_t	info,
	mach_msg_type_number_t	count)
{
	if (processor == PROCESSOR_NULL)
		return(KERN_INVALID_ARGUMENT);

	return(cpu_control(processor->cpu_id, info, count));
}