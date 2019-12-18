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
typedef  int uint32_t ;

/* Variables and functions */
 int MIDR_EL1_REV_MASK ; 
 int MIDR_EL1_REV_SHIFT ; 
 int MIDR_EL1_VAR_MASK ; 
 int MIDR_EL1_VAR_SHIFT ; 
 int get_midr_el1 () ; 

uint32_t get_arm_cpu_version(void)
{
	uint32_t value = get_midr_el1();

	/* Compose the register values into 8 bits; variant[7:4], revision[3:0]. */
	return ((value & MIDR_EL1_REV_MASK) >> MIDR_EL1_REV_SHIFT) | ((value & MIDR_EL1_VAR_MASK) >> (MIDR_EL1_VAR_SHIFT - 4));
}