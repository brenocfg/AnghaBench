#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  ct_key ;
typedef  int /*<<< orphan*/  ct_description ;
typedef  scalar_t__ UINT ;
struct TYPE_6__ {int /*<<< orphan*/  Value; int /*<<< orphan*/  Name; } ;
struct TYPE_5__ {int /*<<< orphan*/  CapsList; } ;
typedef  int /*<<< orphan*/  PACK ;
typedef  TYPE_1__ CAPSLIST ;
typedef  TYPE_2__ CAPS ;

/* Variables and functions */
 int /*<<< orphan*/  Format (char*,int,char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int MAX_PATH ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  PackAddInt (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddIntEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  PackAddStrEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  PackAddUniStrEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  PackSetCurrentJsonGroupName (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  StrToUni (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int UniIsEmptyStr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UniStrCpy (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Zero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * _UU (char*) ; 

void OutRpcCapsList(PACK *p, CAPSLIST *t)
{
	UINT i;
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	PackSetCurrentJsonGroupName(p, "CapsList");
	for (i = 0;i < LIST_NUM(t->CapsList);i++)
	{
		char tmp[MAX_SIZE];
		char ct_key[MAX_PATH];
		wchar_t ct_description[MAX_PATH];
		wchar_t *w;
		CAPS *c = LIST_DATA(t->CapsList, i);

		Format(tmp, sizeof(tmp), "caps_%s", c->Name);

		Format(ct_key, sizeof(ct_key), "CT_%s", c->Name);

		Zero(ct_description, sizeof(ct_description));
		w = _UU(ct_key);
		if (UniIsEmptyStr(w) == false)
		{
			UniStrCpy(ct_description, sizeof(ct_description), w);
		}
		else
		{
			StrToUni(ct_description, sizeof(ct_description), c->Name);
		}

		PackAddInt(p, tmp, c->Value);

		PackAddStrEx(p, "CapsName", c->Name, i, LIST_NUM(t->CapsList));
		PackAddIntEx(p, "CapsValue", c->Value, i, LIST_NUM(t->CapsList));
		PackAddUniStrEx(p, "CapsDescrption", ct_description, i, LIST_NUM(t->CapsList));
	}
	PackSetCurrentJsonGroupName(p, NULL);
}