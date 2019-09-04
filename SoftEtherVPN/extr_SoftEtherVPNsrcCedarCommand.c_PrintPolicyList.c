#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_19__ ;

/* Type definitions */
typedef  char wchar_t ;
typedef  int /*<<< orphan*/  tmp2 ;
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  policy_name ;
typedef  int /*<<< orphan*/  name2 ;
typedef  int /*<<< orphan*/  name1 ;
typedef  int /*<<< orphan*/  name ;
typedef  scalar_t__ UINT ;
struct TYPE_22__ {int /*<<< orphan*/  (* Write ) (TYPE_1__*,char*) ;} ;
struct TYPE_21__ {int /*<<< orphan*/  DefaultValue; } ;
typedef  int /*<<< orphan*/  CT ;
typedef  TYPE_1__ CONSOLE ;

/* Variables and functions */
 char* CopyStrToUni (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CtFree (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  CtInsert (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  CtInsertColumn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/ * CtNew () ; 
 int /*<<< orphan*/  Format (char*,int,char*,scalar_t__) ; 
 int /*<<< orphan*/  FormatPolicyValue (char*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (char*) ; 
 TYPE_19__* GetPolicyItem (scalar_t__) ; 
 int /*<<< orphan*/  GetPolicyValueRangeStr (char*,int,scalar_t__) ; 
 scalar_t__ INFINITE ; 
 scalar_t__ IsEmptyStr (char*) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  PolicyIdToStr (scalar_t__) ; 
 scalar_t__ PolicyNum () ; 
 scalar_t__ PolicyStrToId (char*) ; 
 int /*<<< orphan*/  StrToUni (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UniFormat (char*,int,char*,char*) ; 
 char* _UU (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  stub10 (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  stub11 (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  stub12 (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  stub13 (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  stub14 (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  stub15 (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  stub16 (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  stub4 (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  stub5 (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  stub6 (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  stub7 (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  stub8 (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  stub9 (TYPE_1__*,char*) ; 

void PrintPolicyList(CONSOLE *c, char *name)
{
	UINT id;
	// Validate arguments
	if (c == NULL)
	{
		return;
	}
	if (IsEmptyStr(name))
	{
		name = NULL;
	}

	if (name != NULL)
	{
		id = PolicyStrToId(name);
		if (id == INFINITE)
		{
			// Invalid ID
			c->Write(c, _UU("CMD_PolicyList_Invalid_Name"));
		}
		else
		{
			wchar_t tmp[MAX_SIZE];
			wchar_t tmp2[MAX_SIZE];
			char name1[64], name2[64];
			wchar_t *title, *descript;
			wchar_t policy_name[MAX_SIZE];

			Format(name1, sizeof(name1), "POL_%u", id);
			Format(name2, sizeof(name2), "POL_EX_%u", id);

			title = _UU(name1);
			descript = _UU(name2);

			StrToUni(policy_name, sizeof(policy_name), PolicyIdToStr(id));

			// Policy name
			c->Write(c, _UU("CMD_PolicyList_Help_1"));
			UniFormat(tmp2, sizeof(tmp2), L" %s", policy_name);
			c->Write(c, tmp2);
			c->Write(c, L"");

			// Simple description of the policy
			c->Write(c, _UU("CMD_PolicyList_Help_2"));
			UniFormat(tmp2, sizeof(tmp2), L" %s", title);
			c->Write(c, tmp2);
			c->Write(c, L"");

			// Range of the value that can be set
			GetPolicyValueRangeStr(tmp, sizeof(tmp), id);
			c->Write(c, _UU("CMD_PolicyList_Help_3"));
			UniFormat(tmp2, sizeof(tmp2), L" %s", tmp);
			c->Write(c, tmp2);
			c->Write(c, L"");

			// Default value
			FormatPolicyValue(tmp, sizeof(tmp), id, GetPolicyItem(id)->DefaultValue);
			c->Write(c, _UU("CMD_PolicyList_Help_4"));
			UniFormat(tmp2, sizeof(tmp2), L" %s", tmp);
			c->Write(c, tmp2);
			c->Write(c, L"");

			// Detailed description of the policy
			c->Write(c, _UU("CMD_PolicyList_Help_5"));
			c->Write(c, descript);
			c->Write(c, L"");
		}
	}
	else
	{
		UINT i;
		CT *ct = CtNew();
		CtInsertColumn(ct, _UU("CMD_PolicyList_Column_1"), false);
		CtInsertColumn(ct, _UU("CMD_PolicyList_Column_2"), false);

		// Show the list of all policies
		for (i = 0; i < PolicyNum();i++)
		{
			char name[64];
			wchar_t *tmp;

			tmp = CopyStrToUni(PolicyIdToStr(i));

			Format(name, sizeof(name), "POL_%u", i);
			CtInsert(ct, tmp, _UU(name));

			Free(tmp);
		}

		CtFree(ct, c);
	}
}