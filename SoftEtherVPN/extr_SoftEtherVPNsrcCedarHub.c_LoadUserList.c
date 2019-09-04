#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  UserHashList; int /*<<< orphan*/  Filename; } ;
typedef  TYPE_1__ USERLIST ;
typedef  int /*<<< orphan*/  UINT64 ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  ACCESS_LIST_INCLUDE_FILE_MAX_SIZE ; 
 int /*<<< orphan*/  Add (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  AddInt64Distinct (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* CfgReadNextLine (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Delete (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* FindUserList (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  Free (char*) ; 
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeUserListEntry (TYPE_1__*) ; 
 int IsEmptyStr (char*) ; 
 int /*<<< orphan*/  NewInt64List (int) ; 
 int /*<<< orphan*/ * ReadDumpWithMaxSize (char*,int /*<<< orphan*/ ) ; 
 int StartWith (char*,char*) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  Trim (char*) ; 
 int /*<<< orphan*/  UsernameToInt64 (char*) ; 
 TYPE_1__* ZeroMalloc (int) ; 

USERLIST *LoadUserList(LIST *o, char *filename)
{
	USERLIST *u;
	BUF *b;
	// Validate arguments
	if (o == NULL || filename == NULL)
	{
		return NULL;
	}

	u = FindUserList(o, filename);

	if (u != NULL)
	{
		Delete(o, u);

		FreeUserListEntry(u);
	}

	u = ZeroMalloc(sizeof(USERLIST));

	StrCpy(u->Filename, sizeof(u->Filename), filename);

	u->UserHashList = NewInt64List(false);

	b = ReadDumpWithMaxSize(filename, ACCESS_LIST_INCLUDE_FILE_MAX_SIZE);
	if (b != NULL)
	{
		while (true)
		{
			char *line = CfgReadNextLine(b);
			UINT64 ui;
			if (line == NULL)
			{
				break;
			}

			Trim(line);

			if (IsEmptyStr(line) == false)
			{
				if (StartWith(line, "#") == false &&
					StartWith(line, "//") == false &&
					StartWith(line, ";") == false)
				{
					ui = UsernameToInt64(line);

					AddInt64Distinct(u->UserHashList, ui);
				}
			}

			Free(line);
		}

		FreeBuf(b);
	}

	Add(o, u);

	return u;
}