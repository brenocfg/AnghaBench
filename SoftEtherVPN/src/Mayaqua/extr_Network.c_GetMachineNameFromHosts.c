#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_4__ {int NumTokens; int /*<<< orphan*/ * Token; } ;
typedef  TYPE_1__ TOKEN_LIST ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 char* CfgReadNextLine (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Free (char*) ; 
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeToken (TYPE_1__*) ; 
 TYPE_1__* ParseToken (char*,char*) ; 
 int /*<<< orphan*/ * ReadDump (char*) ; 
 int StartWith (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ StrCmpi (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  StrCpy (char*,size_t,int /*<<< orphan*/ ) ; 

bool GetMachineNameFromHosts(char *name, UINT size)
{
	bool ret = false;
	char *s;
	BUF *b;
	// Validate arguments
	if (name == NULL)
	{
		return false;
	}

	b = ReadDump("/etc/hosts");
	if (b == NULL)
	{
		return false;
	}

	while (true)
	{
		s = CfgReadNextLine(b);
		if (s == NULL)
		{
			break;
		}
		else
		{
			TOKEN_LIST *t = ParseToken(s, " \t");

			if (t != NULL)
			{
				if (t->NumTokens >= 2)
				{
					if (StrCmpi(t->Token[0], "127.0.0.1") == 0)
					{
						UINT i;

						for (i = 1;i < t->NumTokens;i++)
						{
							if (StartWith(t->Token[i], "localhost") == false)
							{
								StrCpy(name, size, t->Token[i]);
								ret = true;
							}
						}
					}
				}
			}
			FreeToken(t);
		}

		Free(s);
	}

	FreeBuf(b);

	return ret;
}