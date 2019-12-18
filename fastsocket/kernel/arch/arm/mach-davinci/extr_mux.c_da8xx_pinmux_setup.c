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
 int EINVAL ; 
 int davinci_cfg_reg (short const) ; 

int da8xx_pinmux_setup(const short pins[])
{
	int i, error = -EINVAL;

	if (pins)
		for (i = 0; pins[i] >= 0; i++) {
			error = davinci_cfg_reg(pins[i]);
			if (error)
				break;
		}

	return error;
}