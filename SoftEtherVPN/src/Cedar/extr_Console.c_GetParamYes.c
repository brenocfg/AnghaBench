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
typedef  int /*<<< orphan*/  LIST ;

/* Variables and functions */
 char* GetParamStr (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ StartWith (char*,char*) ; 
 int /*<<< orphan*/  StrCpy (char*,int,char*) ; 
 scalar_t__ ToInt (char*) ; 
 int /*<<< orphan*/  Trim (char*) ; 

bool GetParamYes(LIST *o, char *name)
{
	char *s;
	char tmp[64];
	// Validate arguments
	if (o == NULL)
	{
		return false;
	}

	s = GetParamStr(o, name);
	if (s == NULL)
	{
		return false;
	}

	StrCpy(tmp, sizeof(tmp), s);
	Trim(tmp);

	if (StartWith(tmp, "y"))
	{
		return true;
	}

	if (StartWith(tmp, "t"))
	{
		return true;
	}

	if (ToInt(tmp) != 0)
	{
		return true;
	}

	return false;
}