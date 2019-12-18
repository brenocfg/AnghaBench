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
 scalar_t__ ToInt (char*) ; 

bool StrToPassOrDiscard(char *str)
{
	// Validate arguments
	if (str == NULL)
	{
		return false;
	}

	if (ToInt(str) != 0)
	{
		return true;
	}

	if (StartWith(str, "p") || StartWith(str, "y") || StartWith(str, "t"))
	{
		return true;
	}

	return false;
}