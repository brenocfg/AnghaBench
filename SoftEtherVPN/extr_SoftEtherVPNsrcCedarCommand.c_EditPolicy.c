#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  tmp2 ;
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  pack_name ;
typedef  scalar_t__ UINT ;
struct TYPE_14__ {int /*<<< orphan*/  (* Write ) (TYPE_4__*,int /*<<< orphan*/ *) ;} ;
struct TYPE_13__ {TYPE_1__** values; } ;
struct TYPE_12__ {int TypeInt; int AllowZero; scalar_t__ MinValue; scalar_t__ MaxValue; } ;
struct TYPE_11__ {int IntValue; } ;
typedef  TYPE_2__ POLICY_ITEM ;
typedef  int /*<<< orphan*/  POLICY ;
typedef  int /*<<< orphan*/  PACK ;
typedef  TYPE_3__ ELEMENT ;
typedef  TYPE_4__ CONSOLE ;

/* Variables and functions */
 int /*<<< orphan*/  Format (char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreePack (int /*<<< orphan*/ *) ; 
 TYPE_3__* GetElement (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* GetPolicyItem (scalar_t__) ; 
 int /*<<< orphan*/  GetPolicyValueRangeStr (int /*<<< orphan*/ *,int,scalar_t__) ; 
 scalar_t__ INFINITE ; 
 int /*<<< orphan*/  InRpcPolicy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/ * NewPack () ; 
 int /*<<< orphan*/  OutRpcPolicy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PolicyIdToStr (scalar_t__) ; 
 int PolicyIsSupportedForCascade (scalar_t__) ; 
 scalar_t__ PolicyStrToId (char*) ; 
 scalar_t__ StartWith (char*,char*) ; 
 scalar_t__ ToInt (char*) ; 
 int /*<<< orphan*/  UniFormat (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  VALUE_INT ; 
 int /*<<< orphan*/  Zero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  _UU (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (TYPE_4__*,int /*<<< orphan*/ *) ; 

bool EditPolicy(CONSOLE *c, POLICY *pol, char *name, char *value, bool cascade_mode)
{
	PACK *p;
	ELEMENT *e;
	POLICY_ITEM *item;
	UINT id;
	wchar_t tmp[MAX_SIZE];
	wchar_t tmp2[MAX_SIZE];
	char pack_name[128];
	// Validate arguments
	if (c == NULL || pol == NULL || name == NULL || value == NULL)
	{
		return false;
	}

	p = NewPack();

	OutRpcPolicy(p, pol);

	Format(pack_name, sizeof(pack_name), "policy:%s", PolicyIdToStr(PolicyStrToId(name)));

	if ((e = GetElement(p, pack_name, VALUE_INT)) == NULL || (id = PolicyStrToId(name)) == INFINITE)
	{
		UniFormat(tmp, sizeof(tmp), _UU("CMD_CascadePolicySet_Invalid_Name"), name);
		c->Write(c, tmp);
		FreePack(p);
		return false;
	}

	if (cascade_mode && (PolicyIsSupportedForCascade(id) == false))
	{
		UniFormat(tmp, sizeof(tmp), _UU("CMD_CascadePolicySet_Invalid_Name_For_Cascade"), name);
		c->Write(c, tmp);
		FreePack(p);
		return false;
	}

	item = GetPolicyItem(id);

	if (item->TypeInt == false)
	{
		// bool type
		e->values[0]->IntValue = (
			StartWith(value, "y") || StartWith(value, "t") ||
			ToInt(value) != 0) ? 1 : 0;
	}
	else
	{
		UINT n = ToInt(value);
		bool b = true;

		// int type
		GetPolicyValueRangeStr(tmp, sizeof(tmp), id);

		if (item->AllowZero == false)
		{
			if (n == 0)
			{
				b = false;
			}
		}

		if (n != 0 && (n < item->MinValue || n > item->MaxValue))
		{
			b = false;
		}

		if (b == false)
		{
			UniFormat(tmp2, sizeof(tmp2), _UU("CMD_CascadePolicySet_Invalid_Range"), PolicyIdToStr(id), tmp);
			c->Write(c, tmp2);
			FreePack(p);
			return false;
		}

		e->values[0]->IntValue = n;
	}

	Zero(pol, sizeof(POLICY));

	InRpcPolicy(pol, p);

	FreePack(p);

	return true;
}