#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  ITEM ;
typedef  int /*<<< orphan*/  FOLDER ;

/* Variables and functions */
 scalar_t__ CalcStrToUni (char*) ; 
 int /*<<< orphan*/ * CfgAddUniStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Malloc (scalar_t__) ; 
 int /*<<< orphan*/  StrToUni (int /*<<< orphan*/ *,scalar_t__,char*) ; 

ITEM *CfgAddStr(FOLDER *f, char *name, char *str)
{
	wchar_t *tmp;
	UINT tmp_size;
	ITEM *t;
	// Validate arguments
	if (f == NULL || name == NULL || str == NULL)
	{
		return NULL;
	}

	// Convert to a Unicode string
	tmp_size = CalcStrToUni(str);
	if (tmp_size == 0)
	{
		return NULL;
	}
	tmp = Malloc(tmp_size);
	StrToUni(tmp, tmp_size, str);
	t = CfgAddUniStr(f, name, tmp);
	Free(tmp);

	return t;
}