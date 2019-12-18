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
 scalar_t__ StartWith (char*,char*) ; 

bool IsNameInRealName(char *input_name, char *real_name)
{
	// Validate arguments
	if (input_name == NULL || real_name == NULL)
	{
		return false;
	}

	if (StartWith(real_name, input_name))
	{
		return true;
	}

	return false;
}