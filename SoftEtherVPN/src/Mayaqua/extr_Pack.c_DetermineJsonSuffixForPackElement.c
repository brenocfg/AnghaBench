#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int type; int JsonHint_IsIP; int JsonHint_IsDateTime; int /*<<< orphan*/  JsonHint_IsBool; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ ELEMENT ;

/* Variables and functions */
 int InStr (int /*<<< orphan*/ ,char*) ; 
#define  VALUE_DATA 132 
#define  VALUE_INT 131 
#define  VALUE_INT64 130 
#define  VALUE_STR 129 
#define  VALUE_UNISTR 128 

char *DetermineJsonSuffixForPackElement(ELEMENT *e)
{
	switch (e->type)
	{
	case VALUE_INT:
		if (e->JsonHint_IsIP)
		{
			if (InStr(e->name, "@") == false)
			{
				return "_ip";
			}
		}
		else if (e->JsonHint_IsBool)
		{
			return "_bool";
		}
		else
		{
			return "_u32";
		}
		break;
	case VALUE_INT64:
		if (e->JsonHint_IsIP == false)
		{
			if (e->JsonHint_IsDateTime == false)
			{
				return "_u64";
			}
			else
			{
				return "_dt";
			}
		}
		break;
	case VALUE_DATA:
		if (e->JsonHint_IsIP == false)
		{
			return "_bin";
		}
		break;
	case VALUE_STR:
		if (e->JsonHint_IsIP == false)
		{
			return "_str";
		}
		break;
	case VALUE_UNISTR:
		if (e->JsonHint_IsIP == false)
		{
			return "_utf";
		}
		break;
	}

	return NULL;
}