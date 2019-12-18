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
typedef  int u8 ;

/* Variables and functions */
 int* to_sas_gpio_gp_bit (unsigned int,int*,int,int,int*) ; 

int try_test_sas_gpio_gp_bit(unsigned int od, u8 *data, u8 index, u8 count)
{
	u8 *byte;
	u8 bit;

	byte = to_sas_gpio_gp_bit(od, data, index, count, &bit);
	if (!byte)
		return -1;

	return (*byte >> bit) & 1;
}