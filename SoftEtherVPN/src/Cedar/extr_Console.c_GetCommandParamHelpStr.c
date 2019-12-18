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
typedef  int /*<<< orphan*/  tmp ;

/* Variables and functions */
 int /*<<< orphan*/  Format (char*,int,char*,char*,char*) ; 
 scalar_t__ UniIsEmptyStr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * _UU (char*) ; 

void GetCommandParamHelpStr(char *command_name, char *param_name, wchar_t **description)
{
	char tmp[160];
	if (description == NULL)
	{
		return;
	}

	Format(tmp, sizeof(tmp), "CMD_%s_%s", command_name, param_name);

	*description = _UU(tmp);

	if (UniIsEmptyStr(*description))
	{
		*description = _UU("CMD_UNKNOWN_PARAM");
	}
}