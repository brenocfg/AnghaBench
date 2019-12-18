#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_9__ {int /*<<< orphan*/ * LangList; int /*<<< orphan*/  LcidList; int /*<<< orphan*/  TitleLocal; int /*<<< orphan*/  TitleEnglish; int /*<<< orphan*/  Name; void* Id; } ;
struct TYPE_8__ {int NumTokens; char** Token; } ;
typedef  TYPE_1__ TOKEN_LIST ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_2__ LANGLIST ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  AddIntDistinct (int /*<<< orphan*/ ,size_t) ; 
 char* CfgReadNextLine (int /*<<< orphan*/ *) ; 
 TYPE_2__* CopyStr (char*) ; 
 int /*<<< orphan*/  Free (char*) ; 
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeToken (TYPE_1__*) ; 
 int IsEmptyStr (char*) ; 
 char* LANGLIST_FILENAME ; 
 char* LANGLIST_FILENAME_WINE ; 
 scalar_t__ MsIsWine () ; 
 int /*<<< orphan*/  NewIntList (int) ; 
 void* NewListFast (int /*<<< orphan*/ *) ; 
 TYPE_1__* ParseToken (char*,char*) ; 
 int /*<<< orphan*/ * ReadDump (char*) ; 
 int StartWith (char*,char*) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  StrLen (char*) ; 
 void* ToInt (char*) ; 
 int /*<<< orphan*/  Trim (char*) ; 
 int /*<<< orphan*/  UniReplaceStrEx (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  Utf8ToUni (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* ZeroMalloc (int) ; 

LIST *LoadLangList()
{
	LIST *o = NewListFast(NULL);
	char *filename = LANGLIST_FILENAME;
	BUF *b;

#ifdef	OS_WIN32
	if (MsIsWine())
	{
		filename = LANGLIST_FILENAME_WINE;
	}
#endif	// OS_WIN32

	b = ReadDump(filename);
	if (b == NULL)
	{
		return NULL;
	}

	while (true)
	{
		char *line = CfgReadNextLine(b);

		if (line == NULL)
		{
			break;
		}

		Trim(line);

		if (IsEmptyStr(line) == false && StartWith(line, "#") == false)
		{
			TOKEN_LIST *t = ParseToken(line, "\t ");
			if (t != NULL)
			{
				if (t->NumTokens == 6)
				{
					LANGLIST *e = ZeroMalloc(sizeof(LANGLIST));
					TOKEN_LIST *t2;

					e->Id = ToInt(t->Token[0]);
					StrCpy(e->Name, sizeof(e->Name), t->Token[1]);
					Utf8ToUni(e->TitleEnglish, sizeof(e->TitleEnglish), t->Token[2], StrLen(t->Token[2]));
					Utf8ToUni(e->TitleLocal, sizeof(e->TitleLocal), t->Token[3], StrLen(t->Token[3]));

					UniReplaceStrEx(e->TitleEnglish, sizeof(e->TitleEnglish), e->TitleEnglish,
						L"_", L" ", true);

					UniReplaceStrEx(e->TitleLocal, sizeof(e->TitleLocal), e->TitleLocal,
						L"_", L" ", true);

					e->LcidList = NewIntList(false);

					t2 = ParseToken(t->Token[4], ",");
					if (t2 != NULL)
					{
						UINT i;

						for (i = 0;i < t2->NumTokens;i++)
						{
							UINT id = ToInt(t2->Token[i]);

							AddIntDistinct(e->LcidList, id);
						}

						FreeToken(t2);
					}

					e->LangList = NewListFast(NULL);

					t2 = ParseToken(t->Token[5], ",");
					if (t2 != NULL)
					{
						UINT i;

						for (i = 0;i < t2->NumTokens;i++)
						{
							Add(e->LangList, CopyStr(t2->Token[i]));
						}

						FreeToken(t2);
					}

					Add(o, e);
				}

				FreeToken(t);
			}
		}

		Free(line);
	}

	FreeBuf(b);

	return o;
}