#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ LatestIgnoreBuild; } ;
struct TYPE_9__ {scalar_t__ MyBuild; scalar_t__ LatestBuild; int /*<<< orphan*/  Param; int /*<<< orphan*/  HaltFlag; int /*<<< orphan*/  (* Callback ) (TYPE_2__*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;TYPE_1__ Setting; int /*<<< orphan*/  FamilyName; } ;
typedef  TYPE_2__ UPDATE_CLIENT ;
typedef  scalar_t__ UINT64 ;
typedef  scalar_t__ UINT ;
struct TYPE_10__ {int NumTokens; int /*<<< orphan*/ * Token; } ;
typedef  TYPE_3__ TOKEN_LIST ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 char* CfgReadNextLine (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Free (char*) ; 
 int /*<<< orphan*/  FreeToken (TYPE_3__*) ; 
 int IsEmptyStr (char*) ; 
 TYPE_3__* ParseTokenWithNullStr (char*,char*) ; 
 int /*<<< orphan*/  SeekBufToBegin (int /*<<< orphan*/ *) ; 
 scalar_t__ ShortStrToDate64 (int /*<<< orphan*/ ) ; 
 int StartWith (char*,char*) ; 
 scalar_t__ StrCmpi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ToInt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Trim (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void UpdateClientThreadProcessResults(UPDATE_CLIENT *c, BUF *b)
{
	bool exit = false;
	// Validate arguments
	if (c == NULL || b == NULL)
	{
		return;
	}

	SeekBufToBegin(b);

	while (true)
	{
		char *line = CfgReadNextLine(b);
		if (line == NULL)
		{
			break;
		}

		Trim(line);

		if (StartWith(line, "#") == false && IsEmptyStr(line) == false)
		{
			TOKEN_LIST *t = ParseTokenWithNullStr(line, " \t");

			if (t != NULL)
			{
				if (t->NumTokens >= 5)
				{
					if (StrCmpi(t->Token[0], c->FamilyName) == 0)
					{
						// Match
						UINT64 date = ShortStrToDate64(t->Token[1]);
						if (date != 0)
						{
							UINT build = ToInt(t->Token[2]);
							if (build != 0)
							{
								if (build > c->MyBuild && build > c->LatestBuild && build > c->Setting.LatestIgnoreBuild)
								{
									c->Callback(c, build, date, t->Token[3], t->Token[4], &c->HaltFlag, c->Param);

									c->LatestBuild = build;

									exit = true;
								}
							}
						}
					}
				}

				FreeToken(t);
			}
		}

		Free(line);

		if (exit)
		{
			break;
		}
	}
}