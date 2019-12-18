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
typedef  int /*<<< orphan*/  tmp ;

/* Variables and functions */
 scalar_t__ IsEmptyStr (char*) ; 
 int MAX_SIZE ; 
 scalar_t__ StartWith (char*,char*) ; 
 int /*<<< orphan*/  StrCpy (char*,int,char*) ; 
 scalar_t__ ToInt (char*) ; 
 int /*<<< orphan*/  Trim (char*) ; 

bool ToBool(char *str)
{
	char tmp[MAX_SIZE];
	// Validate arguments
	if (str == NULL)
	{
		return false;
	}

	StrCpy(tmp, sizeof(tmp), str);
	Trim(tmp);

	if (IsEmptyStr(tmp))
	{
		return false;
	}

	if (ToInt(tmp) != 0)
	{
		return true;
	}

	if (StartWith("true", tmp))
	{
		return true;
	}

	if (StartWith("yes", tmp))
	{
		return true;
	}

	if (StartWith(tmp, "true"))
	{
		return true;
	}

	if (StartWith(tmp, "yes"))
	{
		return true;
	}

	return false;
}