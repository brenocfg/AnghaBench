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
typedef  int /*<<< orphan*/  UINT ;

/* Variables and functions */
 int /*<<< orphan*/  strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

UINT ToInt(char *str)
{
	// Validate arguments
	if (str == NULL)
	{
		return 0;
	}

	// Ignore the octal literal
	while (true)
	{
		if (*str != '0')
		{
			break;
		}
		if ((*(str + 1) == 'x') || (*(str + 1) == 'X'))
		{
			break;
		}
		str++;
	}

	return (UINT)strtoul(str, NULL, 0);
}