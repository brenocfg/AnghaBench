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
typedef  int /*<<< orphan*/  value_str ;
typedef  int /*<<< orphan*/  tmp2 ;
typedef  int /*<<< orphan*/  name ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  POLICY ;
typedef  int /*<<< orphan*/  PACK ;
typedef  int /*<<< orphan*/  CT ;
typedef  int /*<<< orphan*/  CONSOLE ;

/* Variables and functions */
 int /*<<< orphan*/ * CopyStrToUni (scalar_t__) ; 
 int /*<<< orphan*/  CtFree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CtInsert (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CtInsertColumn (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * CtNew () ; 
 int /*<<< orphan*/  Format (char*,int,char*,scalar_t__) ; 
 int /*<<< orphan*/  FormatPolicyValue (int /*<<< orphan*/ *,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreePack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewPack () ; 
 int /*<<< orphan*/  OutRpcPolicy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ PackGetInt (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ PolicyIdToStr (scalar_t__) ; 
 scalar_t__ PolicyIsSupportedForCascade (scalar_t__) ; 
 scalar_t__ PolicyNum () ; 
 int /*<<< orphan*/  _UU (char*) ; 

void PrintPolicy(CONSOLE *c, POLICY *pol, bool cascade_mode)
{
	UINT i;
	CT *ct;
	PACK *p;
	// Validate arguments
	if (c == NULL || pol == NULL)
	{
		return;
	}

	ct = CtNew();
	CtInsertColumn(ct, _UU("CMD_PolicyList_Column_1"), false);
	CtInsertColumn(ct, _UU("CMD_PolicyList_Column_2"), false);
	CtInsertColumn(ct, _UU("CMD_PolicyList_Column_3"), false);

	p = NewPack();
	OutRpcPolicy(p, pol);

	// Show the list of all policies
	for (i = 0; i < PolicyNum();i++)
	{
		char name[64];
		wchar_t *tmp;

		if (cascade_mode == false || PolicyIsSupportedForCascade(i))
		{
			wchar_t value_str[256];
			UINT value;
			char tmp2[256];

			Format(tmp2, sizeof(tmp2), "policy:%s", PolicyIdToStr(i));
			value = PackGetInt(p, tmp2);

			tmp = CopyStrToUni(PolicyIdToStr(i));

			FormatPolicyValue(value_str, sizeof(value_str),
				i, value);

			Format(name, sizeof(name), "POL_%u", i);
			CtInsert(ct, tmp, _UU(name), value_str);

			Free(tmp);
		}
	}

	FreePack(p);

	CtFree(ct, c);
}