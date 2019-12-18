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
typedef  scalar_t__ wchar_t ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_3__ {scalar_t__ Type; int /*<<< orphan*/  Buf; } ;
typedef  TYPE_1__ ITEM ;
typedef  int /*<<< orphan*/  FOLDER ;

/* Variables and functions */
 TYPE_1__* CfgFindItem (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ ITEM_TYPE_STRING ; 
 int /*<<< orphan*/  UniStrCpy (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool CfgGetUniStr(FOLDER *f, char *name, wchar_t *str, UINT size)
{
	ITEM *t;
	// Validate arguments
	if (f == NULL || name == NULL || str == NULL)
	{
		return false;
	}

	str[0] = 0;

	t = CfgFindItem(f, name);
	if (t == NULL)
	{
		return false;
	}
	if (t->Type != ITEM_TYPE_STRING)
	{
		return false;
	}
	UniStrCpy(str, size, t->Buf);
	return true;
}