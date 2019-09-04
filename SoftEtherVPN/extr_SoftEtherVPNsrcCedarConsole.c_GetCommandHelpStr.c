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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  tmp3 ;
typedef  int /*<<< orphan*/  tmp2 ;
typedef  int /*<<< orphan*/  tmp1 ;

/* Variables and functions */
 int /*<<< orphan*/  Format (char*,int,char*,char*) ; 
 scalar_t__ UniIsEmptyStr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * _UU (char*) ; 

void GetCommandHelpStr(char *command_name, wchar_t **description, wchar_t **args, wchar_t **help)
{
	char tmp1[128], tmp2[128], tmp3[128];

	Format(tmp1, sizeof(tmp1), "CMD_%s", command_name);
	Format(tmp2, sizeof(tmp2), "CMD_%s_ARGS", command_name);
	Format(tmp3, sizeof(tmp3), "CMD_%s_HELP", command_name);

	if (description != NULL)
	{
		*description = _UU(tmp1);
		if (UniIsEmptyStr(*description))
		{
			*description = _UU("CMD_UNKNOWM");
		}
	}

	if (args != NULL)
	{
		*args = _UU(tmp2);
		if (UniIsEmptyStr(*args))
		{
			*args = _UU("CMD_UNKNOWN_ARGS");
		}
	}

	if (help != NULL)
	{
		*help = _UU(tmp3);
		if (UniIsEmptyStr(*help))
		{
			*help = _UU("CMD_UNKNOWN_HELP");
		}
	}
}