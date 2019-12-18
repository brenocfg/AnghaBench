#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  current_chain ;
typedef  size_t UINT ;
struct TYPE_11__ {char* Chain; char* ConditionAndArgs; scalar_t__ LineNumber; } ;
struct TYPE_10__ {int /*<<< orphan*/  EntryList; } ;
struct TYPE_9__ {size_t NumTokens; char** Token; } ;
typedef  TYPE_1__ TOKEN_LIST ;
typedef  TYPE_2__ IPTABLES_STATE ;
typedef  TYPE_3__ IPTABLES_ENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  FreeToken (TYPE_1__*) ; 
 int /*<<< orphan*/  NewListFast (int /*<<< orphan*/ *) ; 
 TYPE_1__* ParseToken (char*,char*) ; 
 scalar_t__ StartWith (char*,char*) ; 
 int /*<<< orphan*/  StrCpy (char*,int,char*) ; 
 scalar_t__ ToInt (char*) ; 
 TYPE_1__* UnixExec (char*) ; 
 int /*<<< orphan*/  Zero (char*,int) ; 
 void* ZeroMalloc (int) ; 

IPTABLES_STATE *GetCurrentIpTables()
{
	IPTABLES_STATE *ret = NULL;
	TOKEN_LIST *t = NULL;

#ifdef	OS_UNIX
	t = UnixExec("iptables -L -x -n --line-numbers");
#endif	// OS_UNIX

	if (t != NULL)
	{
		UINT i;
		UINT tmp_num = 0;

		for (i = 0;i < t->NumTokens;i++)
		{
			char *line = t->Token[i];
			if (StartWith(line, "Chain INPUT") ||
				StartWith(line, "Chain FORWARD") ||
				StartWith(line, "Chain OUTPUT"))
			{
				tmp_num++;
			}
		}

		if (tmp_num >= 3)
		{
			char current_chain[64];
			UINT mode = 0;

			Zero(current_chain, sizeof(current_chain));

			for (i = 0;i < t->NumTokens;i++)
			{
				char *line = t->Token[i];

				if (StartWith(line, "Chain"))
				{
					TOKEN_LIST *t2 = ParseToken(line, " \t");
					if (t2 != NULL)
					{
						if (t2->NumTokens >= 4)
						{
							StrCpy(current_chain, sizeof(current_chain), t2->Token[1]);
							mode = 1;

							if (ret == NULL)
							{
								ret = ZeroMalloc(sizeof(IPTABLES_STATE));
								ret->EntryList = NewListFast(NULL);
							}

						}
						FreeToken(t2);
					}
				}

				if (mode == 1)
				{
					if (StartWith(line, "num"))
					{
						mode = 2;
					}
				}
				else if (mode == 2)
				{
					TOKEN_LIST *t2 = ParseToken(line, " \t");
					if (t2 != NULL)
					{
						if (t2->NumTokens >= 6 && ToInt(t2->Token[0]) != 0)
						{
							IPTABLES_ENTRY *e = ZeroMalloc(sizeof(IPTABLES_ENTRY));

							StrCpy(e->Chain, sizeof(e->Chain), current_chain);
							e->LineNumber = ToInt(t2->Token[0]);
							StrCpy(e->ConditionAndArgs, sizeof(e->ConditionAndArgs), line);

							Add(ret->EntryList, e);
						}

						FreeToken(t2);
					}
				}
			}
		}

		FreeToken(t);
	}

	return ret;
}