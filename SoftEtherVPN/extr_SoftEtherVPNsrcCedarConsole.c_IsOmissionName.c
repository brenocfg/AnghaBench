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
typedef  int /*<<< orphan*/  oname ;

/* Variables and functions */
 scalar_t__ EndWith (char*,char*) ; 
 int /*<<< orphan*/  GetOmissionName (char*,int,char*) ; 
 scalar_t__ IsAllUpperStr (char*) ; 
 scalar_t__ IsEmptyStr (char*) ; 
 scalar_t__ StartWith (char*,char*) ; 
 size_t StrLen (char*) ; 

bool IsOmissionName(char *input_name, char *real_name)
{
	char oname[128];
	// Validate arguments
	if (input_name == NULL || real_name == NULL)
	{
		return false;
	}

	if (IsAllUpperStr(real_name))
	{
		// Command of all capital letters do not take abbreviations
		return false;
	}

	GetOmissionName(oname, sizeof(oname), real_name);

	if (IsEmptyStr(oname))
	{
		return false;
	}

	if (StartWith(oname, input_name))
	{
		// Example: The oname of AccountSecureCertSet is "ascs".
		// But if the user enters "asc", returns true
		return true;
	}

	if (StartWith(input_name, oname))
	{
		// Example: When two commands AccountCreate and AccountConnect exist,
		// if the user enter "aconnect" , only AccountConnect is true

		if (EndWith(real_name, &input_name[StrLen(oname)]))
		{
			return true;
		}
	}

	return false;
}