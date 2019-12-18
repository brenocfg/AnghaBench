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
struct TYPE_3__ {int /*<<< orphan*/ * json_subitem_names; int /*<<< orphan*/  CurrentJsonHint_GroupName; } ;
typedef  TYPE_1__ PACK ;

/* Variables and functions */
 int /*<<< orphan*/  AddStrToStrListDistinct (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ClearStr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * NewStrList () ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,char*) ; 

void PackSetCurrentJsonGroupName(PACK *p, char *json_group_name)
{
	if (p == NULL)
	{
		return;
	}

	if (json_group_name == NULL)
	{
		ClearStr(p->CurrentJsonHint_GroupName, sizeof(p->CurrentJsonHint_GroupName));
	}
	else
	{
		StrCpy(p->CurrentJsonHint_GroupName, sizeof(p->CurrentJsonHint_GroupName), json_group_name);

		if (p->json_subitem_names == NULL)
		{
			p->json_subitem_names = NewStrList();
		}

		AddStrToStrListDistinct(p->json_subitem_names, json_group_name);
	}
}