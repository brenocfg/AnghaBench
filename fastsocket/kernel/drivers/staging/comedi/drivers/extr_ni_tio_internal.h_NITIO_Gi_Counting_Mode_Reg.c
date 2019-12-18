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
typedef  enum ni_gpct_register { ____Placeholder_ni_gpct_register } ni_gpct_register ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int NITIO_G0_Counting_Mode_Reg ; 
 int NITIO_G1_Counting_Mode_Reg ; 
 int NITIO_G2_Counting_Mode_Reg ; 
 int NITIO_G3_Counting_Mode_Reg ; 

__attribute__((used)) static inline enum ni_gpct_register NITIO_Gi_Counting_Mode_Reg(unsigned
							       counter_index)
{
	switch (counter_index) {
	case 0:
		return NITIO_G0_Counting_Mode_Reg;
		break;
	case 1:
		return NITIO_G1_Counting_Mode_Reg;
		break;
	case 2:
		return NITIO_G2_Counting_Mode_Reg;
		break;
	case 3:
		return NITIO_G3_Counting_Mode_Reg;
		break;
	default:
		BUG();
		break;
	}
	return 0;
}