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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  tmp2 ;
typedef  int /*<<< orphan*/  tmp1 ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_3__ {int TypeInt; char* FormatStr; int /*<<< orphan*/  MaxValue; int /*<<< orphan*/  MinValue; scalar_t__ AllowZero; } ;
typedef  TYPE_1__ POLICY_ITEM ;

/* Variables and functions */
 TYPE_1__* GetPolicyItem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UniFormat (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  UniStrCpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * _UU (char*) ; 

void GetPolicyValueRangeStr(wchar_t *str, UINT size, UINT id)
{
	POLICY_ITEM *p;
	// Validate arguments
	if (str == NULL)
	{
		return;
	}

	p = GetPolicyItem(id);

	if (p->TypeInt == false)
	{
		// bool type
		UniStrCpy(str, size, _UU("CMD_PolicyList_Range_Bool"));
	}
	else
	{
		wchar_t *tag;
		wchar_t tmp1[256], tmp2[256];

		// int type
		if (p->AllowZero)
		{
			tag = _UU("CMD_PolicyList_Range_Int_2");
		}
		else
		{
			tag = _UU("CMD_PolicyList_Range_Int_1");
		}

		UniFormat(tmp1, sizeof(tmp1), _UU(p->FormatStr), p->MinValue);
		UniFormat(tmp2, sizeof(tmp2), _UU(p->FormatStr), p->MaxValue);

		UniFormat(str, size, tag, tmp1, tmp2);
	}
}