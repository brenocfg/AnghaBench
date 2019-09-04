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
struct TYPE_4__ {char* Name; } ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_1__ LANGLIST ;

/* Variables and functions */
 TYPE_1__* LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 scalar_t__ StartWith (char*,char*) ; 
 scalar_t__ StrCmpi (char*,char*) ; 

LANGLIST *GetBestLangByName(LIST *o, char *name)
{
	UINT i;
	LANGLIST *ret = NULL;
	// Validate arguments
	if (o == NULL)
	{
		return NULL;
	}

	for (i = 0;i < LIST_NUM(o);i++)
	{
		LANGLIST *e = LIST_DATA(o, i);

		if (StrCmpi(e->Name, name) == 0)
		{
			ret = e;
			break;
		}
	}

	if (ret != NULL)
	{
		return ret;
	}

	for (i = 0;i < LIST_NUM(o);i++)
	{
		LANGLIST *e = LIST_DATA(o, i);

		if (StartWith(e->Name, name) || StartWith(name, e->Name))
		{
			ret = e;
			break;
		}
	}

	if (ret != NULL)
	{
		return ret;
	}

	return ret;
}