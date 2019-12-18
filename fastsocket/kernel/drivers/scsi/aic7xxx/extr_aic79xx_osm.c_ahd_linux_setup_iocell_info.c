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
typedef  int uint8_t ;
typedef  size_t u_long ;
typedef  int int32_t ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * aic79xx_iocell_info ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  printf (char*,int,size_t,int) ; 

__attribute__((used)) static void
ahd_linux_setup_iocell_info(u_long index, int instance, int targ, int32_t value)
{

	if ((instance >= 0)
	 && (instance < ARRAY_SIZE(aic79xx_iocell_info))) {
		uint8_t *iocell_info;

		iocell_info = (uint8_t*)&aic79xx_iocell_info[instance];
		iocell_info[index] = value & 0xFFFF;
		if (bootverbose)
			printf("iocell[%d:%ld] = %d\n", instance, index, value);
	}
}