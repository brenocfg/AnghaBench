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
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
#define  PROCESSOR_CPU_STAT 128 
 unsigned int PROCESSOR_CPU_STAT_COUNT ; 

kern_return_t
cpu_info_count(processor_flavor_t flavor,
	       unsigned int *count)
{

	switch (flavor) {
	case PROCESSOR_CPU_STAT:
		*count = PROCESSOR_CPU_STAT_COUNT;
		return (KERN_SUCCESS);

	default:
		*count = 0;
		return (KERN_FAILURE);
	}
}