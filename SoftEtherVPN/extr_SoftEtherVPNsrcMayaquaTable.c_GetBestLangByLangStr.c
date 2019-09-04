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
typedef  scalar_t__ UINT ;
struct TYPE_4__ {int /*<<< orphan*/ * LangList; } ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_1__ LANGLIST ;

/* Variables and functions */
 TYPE_1__* GetBestLangByName (int /*<<< orphan*/ *,char*) ; 
 void* LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 scalar_t__ StartWith (char*,char*) ; 
 scalar_t__ StrCmpi (char*,char*) ; 

LANGLIST *GetBestLangByLangStr(LIST *o, char *str)
{
	UINT i;
	LANGLIST *ret;
	// Validate arguments
	if (o == NULL)
	{
		return NULL;
	}

	for (i = 0;i < LIST_NUM(o);i++)
	{
		LANGLIST *e = LIST_DATA(o, i);
		UINT j;

		for (j = 0;j < LIST_NUM(e->LangList);j++)
		{
			char *v = LIST_DATA(e->LangList, j);

			if (StrCmpi(v, str) == 0)
			{
				return e;
			}
		}
	}

	for (i = 0;i < LIST_NUM(o);i++)
	{
		LANGLIST *e = LIST_DATA(o, i);
		UINT j;

		for (j = 0;j < LIST_NUM(e->LangList);j++)
		{
			char *v = LIST_DATA(e->LangList, j);

			if (StartWith(str, v) || StartWith(v, str))
			{
				return e;
			}
		}
	}

	ret = GetBestLangByName(o, "en");

	return ret;
}