#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_8__ ;
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  char wchar_t ;
typedef  int /*<<< orphan*/  tmp2 ;
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  t ;
typedef  int /*<<< orphan*/  args ;
typedef  scalar_t__ UINT ;
struct TYPE_28__ {char* RadiusUsername; } ;
struct TYPE_27__ {char* CommonName; TYPE_1__* Serial; } ;
struct TYPE_26__ {int /*<<< orphan*/ * UserX; } ;
struct TYPE_25__ {int /*<<< orphan*/  (* Write ) (TYPE_5__*,char*) ;} ;
struct TYPE_24__ {char* member_0; char* member_2; int /*<<< orphan*/ * member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_1; } ;
struct TYPE_23__ {int /*<<< orphan*/  Rpc; int /*<<< orphan*/ * HubName; } ;
struct TYPE_22__ {char* HubName; char* Name; char* Realname; char* Note; char* GroupName; int AuthType; int /*<<< orphan*/ * Policy; int /*<<< orphan*/  NumLogin; int /*<<< orphan*/  Traffic; int /*<<< orphan*/  UpdatedTime; int /*<<< orphan*/  CreatedTime; int /*<<< orphan*/ * AuthData; int /*<<< orphan*/  ExpireTime; } ;
struct TYPE_21__ {int size; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ RPC_SET_USER ;
typedef  TYPE_3__ PS ;
typedef  TYPE_4__ PARAM ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  CT ;
typedef  TYPE_5__ CONSOLE ;
typedef  TYPE_6__ AUTHUSERCERT ;
typedef  TYPE_7__ AUTHROOTCERT ;
typedef  TYPE_8__ AUTHRADIUS ;

/* Variables and functions */
#define  AUTHTYPE_NT 131 
#define  AUTHTYPE_RADIUS 130 
#define  AUTHTYPE_ROOTCERT 129 
#define  AUTHTYPE_USERCERT 128 
 int /*<<< orphan*/  BinToStrEx (char*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CmdEvalNotEmpty ; 
 int /*<<< orphan*/  CmdInsertTrafficInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CmdPrintError (TYPE_5__*,scalar_t__) ; 
 int /*<<< orphan*/  CmdPrompt ; 
 int /*<<< orphan*/  CtFree (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  CtInsert (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/ * CtNewStandard () ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_NO_ERROR ; 
 int /*<<< orphan*/  FreeParamValueList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeRpcSetUser (TYPE_2__*) ; 
 int /*<<< orphan*/  GetAllNameFromX (char*,int,int /*<<< orphan*/ *) ; 
 char* GetAuthTypeStr (int) ; 
 int /*<<< orphan*/  GetDateTimeStrEx64 (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GetParamStr (int /*<<< orphan*/ *,char*) ; 
 int IsEmptyStr (char*) ; 
 int IsEmptyUniStr (char*) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/ * ParseCommandList (TYPE_5__*,char*,char*,TYPE_4__*,int) ; 
 int /*<<< orphan*/  PrintPolicy (TYPE_5__*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ ScGetUser (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  StrCpy (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StrToUni (char*,int,char*) ; 
 int /*<<< orphan*/  SystemToLocal64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UniToStru (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 
 char* _UU (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  stub2 (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  stub3 (TYPE_5__*,char*) ; 

UINT PsUserGet(CONSOLE *c, char *cmd_name, wchar_t *str, void *param)
{
	LIST *o;
	PS *ps = (PS *)param;
	UINT ret = 0;
	RPC_SET_USER t;
	// Parameter list that can be specified
	PARAM args[] =
	{
		// "name", prompt_proc, prompt_param, eval_proc, eval_param
		{"[name]", CmdPrompt, _UU("CMD_UserCreate_Prompt_NAME"), CmdEvalNotEmpty, NULL},
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
	// Get the user object
	StrCpy(t.HubName, sizeof(t.HubName), ps->HubName);
	StrCpy(t.Name, sizeof(t.Name), GetParamStr(o, "[name]"));

	ret = ScGetUser(ps->Rpc, &t);
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
		CT *ct;

		// Display the user's data
		ct = CtNewStandard();

		// User name
		StrToUni(tmp, sizeof(tmp), t.Name);
		CtInsert(ct, _UU("CMD_UserGet_Column_Name"), tmp);

		// Real name
		CtInsert(ct, _UU("CMD_UserGet_Column_RealName"), t.Realname);

		// Description
		CtInsert(ct, _UU("CMD_UserGet_Column_Note"), t.Note);

		// Group name
		if (IsEmptyStr(t.GroupName) == false)
		{
			StrToUni(tmp, sizeof(tmp), t.GroupName);
			CtInsert(ct, _UU("CMD_UserGet_Column_Group"), tmp);
		}

		// Expiration date
		GetDateTimeStrEx64(tmp, sizeof(tmp), SystemToLocal64(t.ExpireTime), NULL);
		CtInsert(ct, _UU("CMD_UserGet_Column_Expires"), tmp);

		// Authentication method
		CtInsert(ct, _UU("CMD_UserGet_Column_AuthType"), GetAuthTypeStr(t.AuthType));

		switch (t.AuthType)
		{
		case AUTHTYPE_USERCERT:
			if (t.AuthData != NULL)
			{
				AUTHUSERCERT *auc = (AUTHUSERCERT *)t.AuthData;

				if (auc != NULL && auc->UserX != NULL)
				{
					// Registered user-specific certificate
					GetAllNameFromX(tmp, sizeof(tmp), auc->UserX);
					CtInsert(ct, _UU("CMD_UserGet_Column_UserCert"), tmp);
				}
			}
			break;

		case AUTHTYPE_ROOTCERT:
			if (t.AuthData != NULL)
			{
				AUTHROOTCERT *arc = (AUTHROOTCERT *)t.AuthData;

				if (IsEmptyUniStr(arc->CommonName) == false)
				{
					// Limitation the value of the certificate's CN
					CtInsert(ct, _UU("CMD_UserGet_Column_RootCert_CN"), arc->CommonName);
				}

				if (arc->Serial != NULL && arc->Serial->size >= 1)
				{
					char tmp2[MAX_SIZE];

					// Limitation the serial number of the certificate
					BinToStrEx(tmp2, sizeof(tmp2), arc->Serial->data, arc->Serial->size);
					StrToUni(tmp, sizeof(tmp), tmp2);
					CtInsert(ct, _UU("CMD_UserGet_Column_RootCert_SERIAL"), tmp);
				}
			}
			break;

		case AUTHTYPE_RADIUS:
		case AUTHTYPE_NT:
			if (t.AuthData != NULL)
			{
				AUTHRADIUS *ar = (AUTHRADIUS *)t.AuthData;

				// Authentication user name of the external authentication server
				if (IsEmptyUniStr(ar->RadiusUsername) == false)
				{
					CtInsert(ct, _UU("CMD_UserGet_Column_RadiusAlias"), ar->RadiusUsername);
				}
			}
			break;
		}

		CtInsert(ct, L"---", L"---");

		GetDateTimeStrEx64(tmp, sizeof(tmp), SystemToLocal64(t.CreatedTime), NULL);
		CtInsert(ct, _UU("SM_USERINFO_CREATE"), tmp);

		GetDateTimeStrEx64(tmp, sizeof(tmp), SystemToLocal64(t.UpdatedTime), NULL);
		CtInsert(ct, _UU("SM_USERINFO_UPDATE"), tmp);

		CmdInsertTrafficInfo(ct, &t.Traffic);

		UniToStru(tmp, t.NumLogin);
		CtInsert(ct, _UU("SM_USERINFO_NUMLOGIN"), tmp);


		CtFree(ct, c);

		if (t.Policy != NULL)
		{
			c->Write(c, L"");
			c->Write(c, _UU("CMD_UserGet_Policy"));
			PrintPolicy(c, t.Policy, false);
		}
	}

	FreeRpcSetUser(&t);

	FreeParamValueList(o);

	return 0;
}