#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct avr32_cpuinfo {int dummy; } ;
struct TYPE_2__ {unsigned int mid; unsigned int pn; char const* name; } ;

/* Variables and functions */
 unsigned int NR_CHIP_NAMES ; 
 unsigned int avr32_get_manufacturer_id (struct avr32_cpuinfo*) ; 
 unsigned int avr32_get_product_number (struct avr32_cpuinfo*) ; 
 TYPE_1__* chip_names ; 

__attribute__((used)) static const char *get_chip_name(struct avr32_cpuinfo *cpu)
{
	unsigned int i;
	unsigned int mid = avr32_get_manufacturer_id(cpu);
	unsigned int pn = avr32_get_product_number(cpu);

	for (i = 0; i < NR_CHIP_NAMES; i++) {
		if (chip_names[i].mid == mid && chip_names[i].pn == pn)
			return chip_names[i].name;
	}

	return "(unknown)";
}