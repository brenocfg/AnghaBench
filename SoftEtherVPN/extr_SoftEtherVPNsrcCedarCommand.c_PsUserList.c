#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  time ;
typedef  int /*<<< orphan*/  t ;
typedef  int /*<<< orphan*/  num2 ;
typedef  int /*<<< orphan*/  num1 ;
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  group ;
typedef  int /*<<< orphan*/  exp ;
typedef  scalar_t__ UINT ;
struct TYPE_22__ {int /*<<< orphan*/  (* Write ) (TYPE_7__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_21__ {int /*<<< orphan*/  Rpc; int /*<<< orphan*/ * HubName; } ;
struct TYPE_20__ {scalar_t__ NumUser; TYPE_4__* Users; int /*<<< orphan*/  HubName; } ;
struct TYPE_17__ {scalar_t__ UnicastCount; scalar_t__ BroadcastBytes; scalar_t__ UnicastBytes; } ;
struct TYPE_16__ {scalar_t__ UnicastCount; scalar_t__ BroadcastCount; scalar_t__ UnicastBytes; scalar_t__ BroadcastBytes; } ;
struct TYPE_18__ {TYPE_2__ Send; TYPE_1__ Recv; } ;
struct TYPE_19__ {scalar_t__ LastLoginTime; int IsExpiresFilled; scalar_t__ Expires; int IsTrafficFilled; int /*<<< orphan*/  AuthType; int /*<<< orphan*/  Note; int /*<<< orphan*/  Realname; TYPE_3__ Traffic; int /*<<< orphan*/  NumLogin; int /*<<< orphan*/  GroupName; int /*<<< orphan*/  Name; } ;
typedef  TYPE_4__ RPC_ENUM_USER_ITEM ;
typedef  TYPE_5__ RPC_ENUM_USER ;
typedef  TYPE_6__ PS ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  CT ;
typedef  TYPE_7__ CONSOLE ;

/* Variables and functions */
 int /*<<< orphan*/  CmdPrintError (TYPE_7__*,scalar_t__) ; 
 int /*<<< orphan*/  CtFreeEx (int /*<<< orphan*/ *,TYPE_7__*,int) ; 
 int /*<<< orphan*/  CtInsert (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CtInsertColumn (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * CtNew () ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_NO_ERROR ; 
 int /*<<< orphan*/  FreeParamValueList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeRpcEnumUser (TYPE_5__*) ; 
 int /*<<< orphan*/  GetAuthTypeStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDateTimeStrEx64 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/ * ParseCommandList (TYPE_7__*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ScEnumUser (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ StrLen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrToUni (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SystemToLocal64 (scalar_t__) ; 
 int /*<<< orphan*/  UniStrCpy (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UniToStr3 (int /*<<< orphan*/ *,int,scalar_t__) ; 
 int /*<<< orphan*/  UniToStru (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_5__*,int) ; 
 int /*<<< orphan*/  _UU (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_7__*,int /*<<< orphan*/ ) ; 

UINT PsUserList(CONSOLE *c, char *cmd_name, wchar_t *str, void *param)
{
	LIST *o;
	PS *ps = (PS *)param;
	UINT ret = 0;
	RPC_ENUM_USER t;

	// If virtual HUB is not selected, it's an error
	if (ps->HubName == NULL)
	{
		c->Write(c, _UU("CMD_Hub_Not_Selected"));
		return ERR_INVALID_PARAMETER;
	}

	o = ParseCommandList(c, cmd_name, str, NULL, 0);
	if (o == NULL)
	{
		return ERR_INVALID_PARAMETER;
	}

	Zero(&t, sizeof(t));
	StrCpy(t.HubName, sizeof(t.HubName), ps->HubName);

	// RPC call
	ret = ScEnumUser(ps->Rpc, &t);

	if (ret != ERR_NO_ERROR)
	{
		// An error has occured
		CmdPrintError(c, ret);
		FreeParamValueList(o);
		return ret;
	}
	else
	{
		UINT i;
		CT *ct = CtNew();

		CtInsertColumn(ct, _UU("SM_USER_COLUMN_1"), false);
		CtInsertColumn(ct, _UU("SM_USER_COLUMN_2"), false);
		CtInsertColumn(ct, _UU("SM_USER_COLUMN_3"), false);
		CtInsertColumn(ct, _UU("SM_USER_COLUMN_4"), false);
		CtInsertColumn(ct, _UU("SM_USER_COLUMN_5"), false);
		CtInsertColumn(ct, _UU("SM_USER_COLUMN_6"), false);
		CtInsertColumn(ct, _UU("SM_USER_COLUMN_7"), false);
		CtInsertColumn(ct, _UU("SM_LICENSE_COLUMN_5"), false);
		CtInsertColumn(ct, _UU("SM_SESS_COLUMN_6"), false);
		CtInsertColumn(ct, _UU("SM_SESS_COLUMN_7"), false);

		for (i = 0;i < t.NumUser;i++)
		{
			RPC_ENUM_USER_ITEM *e = &t.Users[i];
			wchar_t name[MAX_SIZE];
			wchar_t group[MAX_SIZE];
			wchar_t num[MAX_SIZE];
			wchar_t time[MAX_SIZE];
			wchar_t exp[MAX_SIZE];
			wchar_t num1[64], num2[64];

			StrToUni(name, sizeof(name), e->Name);

			if (StrLen(e->GroupName) != 0)
			{
				StrToUni(group, sizeof(group), e->GroupName);
			}
			else
			{
				UniStrCpy(group, sizeof(group), _UU("SM_NO_GROUP"));
			}

			UniToStru(num, e->NumLogin);

			GetDateTimeStrEx64(time, sizeof(time), SystemToLocal64(e->LastLoginTime), NULL);

			if (e->IsExpiresFilled == false)
			{
				UniStrCpy(exp, sizeof(exp), _UU("CM_ST_NONE"));
			}
			else
			{
				if (e->Expires == 0)
				{
					UniStrCpy(exp, sizeof(exp), _UU("SM_LICENSE_NO_EXPIRES"));
				}
				else
				{
					GetDateTimeStrEx64(exp, sizeof(exp), SystemToLocal64(e->Expires), NULL);
				}
			}

			if (e->IsTrafficFilled == false)
			{
				UniStrCpy(num1, sizeof(num1), _UU("CM_ST_NONE"));
				UniStrCpy(num2, sizeof(num2), _UU("CM_ST_NONE"));
			}
			else
			{
				UniToStr3(num1, sizeof(num1),
					e->Traffic.Recv.BroadcastBytes + e->Traffic.Recv.UnicastBytes +
					e->Traffic.Send.BroadcastBytes + e->Traffic.Send.UnicastBytes);

				UniToStr3(num2, sizeof(num2),
					e->Traffic.Recv.BroadcastCount + e->Traffic.Recv.UnicastCount +
					e->Traffic.Send.BroadcastBytes + e->Traffic.Send.UnicastCount);
			}

			CtInsert(ct,
				name, e->Realname, group, e->Note, GetAuthTypeStr(e->AuthType),
				num, time, exp, num1, num2);
		}

		CtFreeEx(ct, c, true);
	}

	FreeRpcEnumUser(&t);

	FreeParamValueList(o);

	return 0;
}