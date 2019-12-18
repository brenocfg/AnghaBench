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
 int l1_data_A_sram_free (void const*) ; 
 int l1_data_B_sram_free (void const*) ; 

int l1_data_sram_free(const void *addr)
{
	int ret;
	ret = l1_data_A_sram_free(addr);
	if (ret == -1)
		ret = l1_data_B_sram_free(addr);
	return ret;
}