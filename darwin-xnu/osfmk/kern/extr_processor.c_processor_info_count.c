#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int processor_flavor_t ;
typedef  int /*<<< orphan*/  mach_msg_type_number_t ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_SUCCESS ; 
#define  PROCESSOR_BASIC_INFO 129 
 int /*<<< orphan*/  PROCESSOR_BASIC_INFO_COUNT ; 
#define  PROCESSOR_CPU_LOAD_INFO 128 
 int /*<<< orphan*/  PROCESSOR_CPU_LOAD_INFO_COUNT ; 
 int /*<<< orphan*/  cpu_info_count (int,int /*<<< orphan*/ *) ; 

kern_return_t
processor_info_count(
	processor_flavor_t		flavor,
	mach_msg_type_number_t	*count)
{
	switch (flavor) {

	case PROCESSOR_BASIC_INFO:
		*count = PROCESSOR_BASIC_INFO_COUNT;
		break;

	case PROCESSOR_CPU_LOAD_INFO:
		*count = PROCESSOR_CPU_LOAD_INFO_COUNT;
		break;

	default:
		return (cpu_info_count(flavor, count));
	}

	return (KERN_SUCCESS);
}