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
typedef  int UINT ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 char* CfgReadNextLine (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Format (char*,int,char*,char*) ; 
 int /*<<< orphan*/  Free (char*) ; 
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ *) ; 
 int IsEmptyStr (char*) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/ * ReadDump (char*) ; 
 scalar_t__ StartWith (char*,char*) ; 
 int /*<<< orphan*/  StrCpy (char*,int,char*) ; 
 int /*<<< orphan*/  Trim (char*) ; 

bool EthGetInterfaceDescriptionUnix(char *name, char *str, UINT size)
{
	char tmp[MAX_SIZE];
	bool ret = false;
	BUF *b;
	// Validate arguments
	if (name == NULL || str == NULL)
	{
		return false;
	}

	StrCpy(str, size, name);

	Format(tmp, sizeof(tmp), "/etc/sysconfig/networking/devices/ifcfg-%s", name);

	b = ReadDump(tmp);
	if (b != NULL)
	{
		char *line = CfgReadNextLine(b);

		if (IsEmptyStr(line) == false)
		{
			if (StartWith(line, "#"))
			{
				char tmp[MAX_SIZE];

				StrCpy(tmp, sizeof(tmp), line + 1);

				Trim(tmp);
				tmp[60] = 0;

				StrCpy(str, size, tmp);

				ret = true;
			}
		}

		Free(line);

		FreeBuf(b);
	}

	return ret;
}