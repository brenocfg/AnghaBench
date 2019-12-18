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

/* Variables and functions */
 scalar_t__ KERNEL_START ; 
 scalar_t__ ia64_tpa (scalar_t__) ; 
 int is_xencomm_initialized ; 
 scalar_t__ kernel_virtual_offset ; 

void
xencomm_initialize(void)
{
	kernel_virtual_offset = KERNEL_START - ia64_tpa(KERNEL_START);
	is_xencomm_initialized = 1;
}