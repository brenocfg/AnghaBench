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
typedef  char wchar_t ;
struct TYPE_3__ {char* unistr; } ;
typedef  TYPE_1__ TABLE ;

/* Variables and functions */
 TYPE_1__* FindTable (char*) ; 

wchar_t *GetTableUniStr(char *name)
{
	TABLE *t;
	// Validate arguments
	if (name == NULL)
	{
//		Debug("%s: ************\n", name);
		return L"";
	}

	// Search
	t = FindTable(name);
	if (t == NULL)
	{
		//Debug("%s: UNICODE STRING NOT FOUND\n", name);
		return L"";
	}

	return t->unistr;
}