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
typedef  int /*<<< orphan*/  LIST ;

/* Variables and functions */
 int /*<<< orphan*/  CiFreeIni (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CiLoadIni () ; 
 char* IniStrValue (int /*<<< orphan*/ *,char*) ; 
 int IsEmptyStr (char*) ; 
 int /*<<< orphan*/  NormalizePath (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  StrCpy (char*,int /*<<< orphan*/ ,char*) ; 

bool CiLoadConfigFilePathFromIni(char *path, UINT size)
{
	char *tmp;
	LIST *o;
	bool ret = false;

	// Validate arguments
	if (path == NULL)
	{
		return false;
	}

	o = CiLoadIni();

	if (o == NULL)
	{
		return false;
	}

	StrCpy(path, size, "");

	tmp = IniStrValue(o, "ConfigPath");
	NormalizePath(path, size, tmp);

	if (IsEmptyStr(path) == false)
	{
		ret = true;
	}
	else
	{
		ret = false;
	}

	CiFreeIni(o);

	return ret;
}