#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;

/* Type definitions */
typedef  char wchar_t ;
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  t ;
typedef  int /*<<< orphan*/  groupname ;
typedef  int /*<<< orphan*/  args ;
typedef  scalar_t__ UINT ;
struct TYPE_29__ {int /*<<< orphan*/  (* Write ) (TYPE_6__*,char*) ;} ;
struct TYPE_28__ {char* member_0; char* member_2; int /*<<< orphan*/ * member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_1; } ;
struct TYPE_27__ {char* HubName; int /*<<< orphan*/  Rpc; } ;
struct TYPE_26__ {int /*<<< orphan*/  Name; int /*<<< orphan*/  GroupName; } ;
struct TYPE_25__ {char* HubName; char* Name; char* Realname; char* Note; scalar_t__ NumUser; TYPE_2__* Users; int /*<<< orphan*/ * Policy; } ;
typedef  TYPE_1__ RPC_SET_GROUP ;
typedef  TYPE_2__ RPC_ENUM_USER_ITEM ;
typedef  TYPE_1__ RPC_ENUM_USER ;
typedef  TYPE_4__ PS ;
typedef  TYPE_5__ PARAM ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  CT ;
typedef  TYPE_6__ CONSOLE ;

/* Variables and functions */
 int /*<<< orphan*/  CmdEvalNotEmpty ; 
 int /*<<< orphan*/  CmdPrintError (TYPE_6__*,scalar_t__) ; 
 int /*<<< orphan*/  CmdPrompt ; 
 int /*<<< orphan*/  CtFree (int /*<<< orphan*/ *,TYPE_6__*) ; 
 int /*<<< orphan*/  CtInsert (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/ * CtNewStandard () ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_NO_ERROR ; 
 int /*<<< orphan*/  FreeParamValueList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeRpcEnumUser (TYPE_1__*) ; 
 int /*<<< orphan*/  FreeRpcSetGroup (TYPE_1__*) ; 
 char* GetParamStr (int /*<<< orphan*/ *,char*) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  MAX_USERNAME_LEN ; 
 int /*<<< orphan*/ * ParseCommandList (TYPE_6__*,char*,char*,TYPE_5__*,int) ; 
 int /*<<< orphan*/  PrintPolicy (TYPE_6__*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ ScEnumUser (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ ScGetGroup (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ StrCmpi (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  StrCpy (char*,int,char*) ; 
 int /*<<< orphan*/  StrToUni (char*,int,char*) ; 
 int /*<<< orphan*/  UniFormat (char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 
 char* _UU (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*,char*) ; 
 int /*<<< orphan*/  stub2 (TYPE_6__*,char*) ; 
 int /*<<< orphan*/  stub3 (TYPE_6__*,char*) ; 
 int /*<<< orphan*/  stub4 (TYPE_6__*,char*) ; 
 int /*<<< orphan*/  stub5 (TYPE_6__*,char*) ; 
 int /*<<< orphan*/  stub6 (TYPE_6__*,char*) ; 
 int /*<<< orphan*/  stub7 (TYPE_6__*,char*) ; 

UINT PsGroupGet(CONSOLE *c, char *cmd_name, wchar_t *str, void *param)
{
	LIST *o;
	PS *ps = (PS *)param;
	UINT ret = 0;
	RPC_SET_GROUP t;
	// Parameter list that can be specified
	PARAM args[] =
	{
		// "name", prompt_proc, prompt_param, eval_proc, eval_param
		{"[name]", CmdPrompt, _UU("CMD_GroupCreate_Prompt_NAME"), CmdEvalNotEmpty, NULL},
	};

	// If virtual HUB is not selected, it's an error
	if (ps->HubName == NULL)
	{
		c->Write(c, _UU("CMD_Hub_Not_Selected"));
		return ERR_INVALID_PARAMETER;
	}

	o = ParseCommandList(c, cmd_name, str, args, sizeof(args) / sizeof(args[0]));
	if (o == NULL)
	{
		return ERR_INVALID_PARAMETER;
	}

	Zero(&t, sizeof(t));
	StrCpy(t.HubName, sizeof(t.HubName), ps->HubName);
	StrCpy(t.Name, sizeof(t.Name), GetParamStr(o, "[name]"));

	// RPC call
	ret = ScGetGroup(ps->Rpc, &t);

	if (ret != ERR_NO_ERROR)
	{
		// An error has occured
		CmdPrintError(c, ret);
		FreeParamValueList(o);
		return ret;
	}
	else
	{
		wchar_t tmp[MAX_SIZE];
		char groupname[MAX_USERNAME_LEN + 1];
		CT *ct = CtNewStandard();

		StrCpy(groupname, sizeof(groupname), t.Name);

		StrToUni(tmp, sizeof(tmp), t.Name);
		CtInsert(ct, _UU("CMD_GroupGet_Column_NAME"), tmp);
		CtInsert(ct, _UU("CMD_GroupGet_Column_REALNAME"), t.Realname);
		CtInsert(ct, _UU("CMD_GroupGet_Column_NOTE"), t.Note);

		CtFree(ct, c);

		if (t.Policy != NULL)
		{
			c->Write(c, L"");
			c->Write(c, _UU("CMD_GroupGet_Column_POLICY"));

			PrintPolicy(c, t.Policy, false);
		}

		{
			RPC_ENUM_USER t;
			bool b = false;

			Zero(&t, sizeof(t));

			StrCpy(t.HubName, sizeof(t.HubName), ps->HubName);

			if (ScEnumUser(ps->Rpc, &t) == ERR_NO_ERROR)
			{
				UINT i;

				for (i = 0;i < t.NumUser;i++)
				{
					RPC_ENUM_USER_ITEM *u = &t.Users[i];

					if (StrCmpi(u->GroupName, groupname) == 0)
					{
						if (b == false)
						{
							b = true;
							c->Write(c, L"");
							c->Write(c, _UU("CMD_GroupGet_Column_MEMBERS"));
						}

						UniFormat(tmp, sizeof(tmp), L" %S", u->Name);
						c->Write(c, tmp);
					}
				}
				FreeRpcEnumUser(&t);

				if (b)
				{
					c->Write(c, L"");
				}
			}
		}

	}

	FreeRpcSetGroup(&t);

	FreeParamValueList(o);

	return 0;
}