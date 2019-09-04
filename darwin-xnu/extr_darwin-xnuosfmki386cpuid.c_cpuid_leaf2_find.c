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
typedef  scalar_t__ uint8_t ;
struct TYPE_4__ {scalar_t__ value; } ;
typedef  TYPE_1__ cpuid_cache_descriptor_t ;

/* Variables and functions */
 unsigned int INTEL_LEAF2_DESC_NUM ; 
 TYPE_1__* intel_cpuid_leaf2_descriptor_table ; 

__attribute__((used)) static inline cpuid_cache_descriptor_t *
cpuid_leaf2_find(uint8_t value)
{
	unsigned int	i;

	for (i = 0; i < INTEL_LEAF2_DESC_NUM; i++)
		if (intel_cpuid_leaf2_descriptor_table[i].value == value)
			return &intel_cpuid_leaf2_descriptor_table[i];
	return NULL;
}