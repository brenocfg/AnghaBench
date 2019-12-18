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

int viafb_input_parameter_converter(int parameter_value)
{
	int result;

	if (parameter_value >= 1 && parameter_value <= 9)
		result = 1 << (parameter_value - 1);
	else
		result = 1;

	return result;
}