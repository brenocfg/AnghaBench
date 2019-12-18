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
 unsigned int AMB_CONFIG_SIZE ; 
 unsigned long AMB_FUNC_3_OFFSET ; 
 unsigned long AMB_REG_TEMP_ADDR ; 

__attribute__((used)) static unsigned long amb_reg_temp(unsigned int amb)
{
	return AMB_FUNC_3_OFFSET + AMB_REG_TEMP_ADDR +
	       AMB_CONFIG_SIZE * amb;
}