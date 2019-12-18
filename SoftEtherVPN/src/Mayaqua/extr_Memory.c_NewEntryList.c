#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  value ;
typedef  int /*<<< orphan*/  key ;
typedef  size_t UINT ;
struct TYPE_8__ {void* Value; void* Key; } ;
struct TYPE_7__ {size_t NumTokens; char** Token; } ;
typedef  TYPE_1__ TOKEN_LIST ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_2__ INI_ENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ *,TYPE_2__*) ; 
 void* CopyStr (char*) ; 
 int /*<<< orphan*/  FreeToken (TYPE_1__*) ; 
 scalar_t__ GetKeyAndValue (char*,char*,int,char*,int,char*) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/ * NewListFast (int /*<<< orphan*/ *) ; 
 TYPE_1__* ParseTokenWithoutNullStr (char*,char*) ; 
 int /*<<< orphan*/  Trim (char*) ; 
 TYPE_2__* ZeroMalloc (int) ; 

LIST *NewEntryList(char *src, char *key_separator, char *value_separator)
{
	LIST *o = NewListFast(NULL);
	TOKEN_LIST *t;

	t = ParseTokenWithoutNullStr(src, key_separator);
	if (t != NULL)
	{
		UINT i;

		for (i = 0; i < t->NumTokens; i++)
		{
			char key[MAX_SIZE];
			char value[MAX_SIZE];
			char *line = t->Token[i];
			Trim(line);

			if (GetKeyAndValue(line, key, sizeof(key), value, sizeof(value), value_separator))
			{
				INI_ENTRY *e = ZeroMalloc(sizeof(INI_ENTRY));

				e->Key = CopyStr(key);
				e->Value = CopyStr(value);

				Add(o, e);
			}
		}

		FreeToken(t);
	}

	return o;
}