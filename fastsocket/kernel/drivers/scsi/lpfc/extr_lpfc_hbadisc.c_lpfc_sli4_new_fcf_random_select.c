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
struct lpfc_hba {int dummy; } ;

/* Variables and functions */
 int random32 () ; 

__attribute__((used)) static bool
lpfc_sli4_new_fcf_random_select(struct lpfc_hba *phba, uint32_t fcf_cnt)
{
	uint32_t rand_num;

	/* Get 16-bit uniform random number */
	rand_num = (0xFFFF & random32());

	/* Decision with probability 1/fcf_cnt */
	if ((fcf_cnt * rand_num) < 0xFFFF)
		return true;
	else
		return false;
}