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
 int NITIO_G01_Joint_Status2_Reg ; 
 int NITIO_G23_Joint_Status2_Reg ; 

__attribute__((used)) static inline enum ni_gpct_register NITIO_Gxx_Joint_Status2_Reg(unsigned
								counter_index)
{
	switch (counter_index) {
	case 0:
	case 1:
		return NITIO_G01_Joint_Status2_Reg;
		break;
	case 2:
	case 3:
		return NITIO_G23_Joint_Status2_Reg;
		break;
	default:
		BUG();
		break;
	}
	return 0;
}