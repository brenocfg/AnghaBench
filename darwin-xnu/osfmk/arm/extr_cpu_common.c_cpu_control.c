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
typedef  int /*<<< orphan*/  processor_info_t ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  printf (char*,int,int /*<<< orphan*/ ,unsigned int) ; 

kern_return_t
cpu_control(int slot_num,
	    processor_info_t info,
	    unsigned int count)
{
	printf("cpu_control(%d,%p,%d) not implemented\n",
	       slot_num, info, count);
	return (KERN_FAILURE);
}