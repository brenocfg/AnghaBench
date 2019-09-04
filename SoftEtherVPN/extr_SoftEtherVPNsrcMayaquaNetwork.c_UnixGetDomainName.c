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
typedef  int /*<<< orphan*/  UINT ;
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
 scalar_t__ StrCmpi (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  StrCpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Trim (char*) ; 

bool UnixGetDomainName(char *name, UINT size)
{
	bool ret = false;
	BUF *b = ReadDump("/etc/resolv.conf");

	if (b == NULL)
	{
		return false;
	}

	while (true)
	{
		char *s = CfgReadNextLine(b);
		TOKEN_LIST *t;

		if (s == NULL)
		{
			break;
		}

		Trim(s);

		t = ParseToken(s, " \t");
		if (t != NULL)
		{
			if (t->NumTokens == 2)
			{
				if (StrCmpi(t->Token[0], "domain") == 0)
				{
					StrCpy(name, size, t->Token[1]);
					ret = true;
				}
			}
			FreeToken(t);
		}

		Free(s);
	}

	FreeBuf(b);

	return ret;
}