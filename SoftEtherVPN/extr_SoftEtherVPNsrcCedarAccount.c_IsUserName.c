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
typedef  scalar_t__ UINT ;

/* Variables and functions */
 char* ADMINISTRATOR_USERNAME ; 
 char* BRIDGE_USER_NAME ; 
 char* BRIDGE_USER_NAME_PRINT ; 
 int IsSafeChar (char) ; 
 int /*<<< orphan*/  L3_USERNAME ; 
 char* LINK_USER_NAME ; 
 char* LINK_USER_NAME_PRINT ; 
 int MAX_SIZE ; 
 char* SNAT_USER_NAME ; 
 char* SNAT_USER_NAME_PRINT ; 
 scalar_t__ StartWith (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ StrCmpi (char*,char*) ; 
 int /*<<< orphan*/  StrCpy (char*,int,char*) ; 
 scalar_t__ StrLen (char*) ; 
 int /*<<< orphan*/  Trim (char*) ; 

bool IsUserName(char *name)
{
	UINT i, len;
	char tmp[MAX_SIZE];
	// Validate arguments
	if (name == NULL)
	{
		return false;
	}

	StrCpy(tmp, sizeof(tmp), name);
	name = tmp;

	Trim(name);

	len = StrLen(name);
	if (len == 0)
	{
		return false;
	}

	if (StrCmpi(name, "*") == 0)
	{
		return true;
	}

	for (i = 0; i < len; i++)
	{
		if (IsSafeChar(name[i]) == false && name[i] != '@')
		{
			return false;
		}
	}

	if (StrCmpi(name, LINK_USER_NAME) == 0)
	{
		return false;
	}

	if (StartWith(name, L3_USERNAME))
	{
		return false;
	}

	if (StrCmpi(name, LINK_USER_NAME_PRINT) == 0)
	{
		return false;
	}

	if (StrCmpi(name, SNAT_USER_NAME) == 0)
	{
		return false;
	}

	if (StrCmpi(name, SNAT_USER_NAME_PRINT) == 0)
	{
		return false;
	}

	if (StrCmpi(name, BRIDGE_USER_NAME) == 0)
	{
		return false;
	}

	if (StrCmpi(name, BRIDGE_USER_NAME_PRINT) == 0)
	{
		return false;
	}

	if (StrCmpi(name, ADMINISTRATOR_USERNAME) == 0)
	{
		return false;
	}

	return true;
}