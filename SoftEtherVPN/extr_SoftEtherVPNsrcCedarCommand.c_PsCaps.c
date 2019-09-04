#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  title ;
typedef  int /*<<< orphan*/  name ;
typedef  scalar_t__ UINT ;
struct TYPE_9__ {scalar_t__ Value; scalar_t__ Name; } ;
struct TYPE_8__ {int /*<<< orphan*/  CapsList; } ;
struct TYPE_7__ {int /*<<< orphan*/  Rpc; } ;
typedef  TYPE_1__ PS ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  CT ;
typedef  int /*<<< orphan*/  CONSOLE ;
typedef  TYPE_2__ CAPSLIST ;
typedef  TYPE_3__ CAPS ;

/* Variables and functions */
 int /*<<< orphan*/  CtFree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CtInsert (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CtNewStandard () ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  Format (char*,int,char*,scalar_t__) ; 
 int /*<<< orphan*/  FreeCapsList (TYPE_2__*) ; 
 int /*<<< orphan*/  FreeParamValueList (int /*<<< orphan*/ *) ; 
 TYPE_3__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/ * ParseCommandList (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* ScGetCapsEx (int /*<<< orphan*/ ) ; 
 scalar_t__ StartWith (scalar_t__,char*) ; 
 scalar_t__ StrCmpi (scalar_t__,char*) ; 
 int StrLen (scalar_t__) ; 
 int /*<<< orphan*/  UniFormat (int /*<<< orphan*/ *,int,char*,scalar_t__) ; 
 scalar_t__ UniIsEmptyStr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UniStrCpy (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UniToStru (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * _UU (char*) ; 

UINT PsCaps(CONSOLE *c, char *cmd_name, wchar_t *str, void *param)
{
	LIST *o;
	PS *ps = (PS *)param;
	CAPSLIST *t;
	UINT i;
	CT *ct;


	o = ParseCommandList(c, cmd_name, str, NULL, 0);
	if (o == NULL)
	{
		return ERR_INVALID_PARAMETER;
	}

	// RPC call
	t = ScGetCapsEx(ps->Rpc);

	ct = CtNewStandard();

	for (i = 0;i < LIST_NUM(t->CapsList);i++)
	{
		CAPS *c = LIST_DATA(t->CapsList, i);
		wchar_t title[MAX_SIZE];
		char name[256];

		Format(name, sizeof(name), "CT_%s", c->Name);

		UniStrCpy(title, sizeof(title), _UU(name));

		if (UniIsEmptyStr(title))
		{
			UniFormat(title, sizeof(title), L"%S", (StrLen(c->Name) >= 2) ? c->Name + 2 : c->Name);
		}

		if (StartWith(c->Name, "b_"))
		{
			bool icon_pass = c->Value == 0 ? false : true;
			if (StrCmpi(c->Name, "b_must_install_pcap") == 0)
			{
				// Reverse only item of WinPcap
				icon_pass = !icon_pass;
			}
			CtInsert(ct, title, c->Value == 0 ? _UU("CAPS_NO") : _UU("CAPS_YES"));
		}
		else
		{
			wchar_t str[64];
			UniToStru(str, c->Value);
			CtInsert(ct, title, str);
		}
	}

	CtFree(ct, c);

	FreeCapsList(t);

	FreeParamValueList(o);

	return 0;
}