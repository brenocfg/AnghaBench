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
 scalar_t__ L1_CODE_LENGTH ; 
 scalar_t__ L1_DATA_A_LENGTH ; 
 scalar_t__ L1_DATA_B_LENGTH ; 
 scalar_t__ L2_LENGTH ; 
 scalar_t__ L2_START ; 
 scalar_t__ get_l1_code_start () ; 
 scalar_t__ get_l1_data_a_start () ; 
 scalar_t__ get_l1_data_b_start () ; 
 int l1_data_A_sram_free (void const*) ; 
 int l1_data_B_sram_free (void const*) ; 
 int l1_inst_sram_free (void const*) ; 
 int l2_sram_free (void const*) ; 

int sram_free(const void *addr)
{

#if L1_CODE_LENGTH != 0
	if (addr >= (void *)get_l1_code_start()
		 && addr < (void *)(get_l1_code_start() + L1_CODE_LENGTH))
		return l1_inst_sram_free(addr);
	else
#endif
#if L1_DATA_A_LENGTH != 0
	if (addr >= (void *)get_l1_data_a_start()
		 && addr < (void *)(get_l1_data_a_start() + L1_DATA_A_LENGTH))
		return l1_data_A_sram_free(addr);
	else
#endif
#if L1_DATA_B_LENGTH != 0
	if (addr >= (void *)get_l1_data_b_start()
		 && addr < (void *)(get_l1_data_b_start() + L1_DATA_B_LENGTH))
		return l1_data_B_sram_free(addr);
	else
#endif
#if L2_LENGTH != 0
	if (addr >= (void *)L2_START
		 && addr < (void *)(L2_START + L2_LENGTH))
		return l2_sram_free(addr);
	else
#endif
		return -1;
}