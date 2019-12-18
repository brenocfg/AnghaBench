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
typedef  unsigned int uint32_t ;

/* Variables and functions */
 int CCV_CLI_NONE ; 

int ccv_cli_output_level_and_above(int level)
{
	if (level == CCV_CLI_NONE)
		return CCV_CLI_NONE;
	int i;
	uint32_t levels = 0;
	for (i = 0; i < 32; i++)
		if (level <= (1u << i))
			levels |= 1u << i;
	return (int)levels;
}