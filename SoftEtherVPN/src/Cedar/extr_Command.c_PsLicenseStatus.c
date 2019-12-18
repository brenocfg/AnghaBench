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
typedef  char wchar_t ;
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  st ;
typedef  int /*<<< orphan*/  dtstr ;
typedef  scalar_t__ UINT ;
struct TYPE_6__ {int /*<<< orphan*/  CapsList; int /*<<< orphan*/  Rpc; } ;
struct TYPE_5__ {scalar_t__ EditionId; scalar_t__ ReleaseDate; char* SystemId; scalar_t__ SystemExpires; int NeedSubscription; scalar_t__ SubscriptionExpires; scalar_t__ NumClientConnectLicense; scalar_t__ NumBridgeConnectLicense; scalar_t__ AllowEnterpriseFunction; scalar_t__ IsSubscriptionExpired; int /*<<< orphan*/  EditionStr; } ;
typedef  TYPE_1__ RPC_LICENSE_STATUS ;
typedef  TYPE_2__ PS ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  CT ;
typedef  int /*<<< orphan*/  CONSOLE ;

/* Variables and functions */
 int /*<<< orphan*/  CmdPrintError (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  CtFreeEx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  CtInsert (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/ * CtNewStandard () ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_NO_ERROR ; 
 int /*<<< orphan*/  FreeParamValueList (int /*<<< orphan*/ *) ; 
 scalar_t__ GetCapsBool (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GetDateStrEx64 (char*,int,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ INFINITE ; 
 scalar_t__ LICENSE_EDITION_VPN3_NO_LICENSE ; 
 int MAX_PATH ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/ * ParseCommandList (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ScGetLicenseStatus (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  StrToUni (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UniFormat (char*,int,char*,char*) ; 
 int /*<<< orphan*/  UniStrCpy (char*,int,char*) ; 
 int /*<<< orphan*/  UniToStru (char*,scalar_t__) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 
 char* _UU (char*) ; 

UINT PsLicenseStatus(CONSOLE *c, char *cmd_name, wchar_t *str, void *param)
{
	LIST *o;
	PS *ps = (PS *)param;
	UINT ret = 0;
	RPC_LICENSE_STATUS st;
	CT *ct;
	wchar_t tmp[MAX_SIZE];

	o = ParseCommandList(c, cmd_name, str, NULL, 0);
	if (o == NULL)
	{
		return ERR_INVALID_PARAMETER;
	}

	Zero(&st, sizeof(st));

	// RPC call
	ret = ScGetLicenseStatus(ps->Rpc, &st);

	if (ret != ERR_NO_ERROR)
	{
		// An error has occured
		CmdPrintError(c, ret);
		FreeParamValueList(o);
		return ret;
	}

	ct = CtNewStandard();

	if (st.EditionId == LICENSE_EDITION_VPN3_NO_LICENSE)
	{
		CtInsert(ct, _UU("SM_NO_LICENSE_COLUMN"), _UU("SM_NO_LICENSE"));
	}
	else
	{
		// Product edition name
		StrToUni(tmp, sizeof(tmp), st.EditionStr);
		CtInsert(ct, _UU("SM_LICENSE_STATUS_EDITION"), tmp);

		// Release date
		if (st.ReleaseDate != 0)
		{
			GetDateStrEx64(tmp, sizeof(tmp), st.ReleaseDate, NULL);
			CtInsert(ct, _UU("SM_LICENSE_STATUS_RELEASE"), tmp);
		}

		// Current system ID
		UniFormat(tmp, sizeof(tmp), L"%I64u", st.SystemId);
		CtInsert(ct, _UU("SM_LICENSE_STATUS_SYSTEM_ID"), tmp);

		// Expiration date of the current license product
		if (st.SystemExpires == 0)
		{
			UniStrCpy(tmp, sizeof(tmp), _UU("SM_LICENSE_NO_EXPIRES"));
		}
		else
		{
			GetDateStrEx64(tmp, sizeof(tmp), st.SystemExpires, NULL);
		}
		CtInsert(ct,  _UU("SM_LICENSE_STATUS_EXPIRES"), tmp);

		// Subscription (support) contract
		if (st.NeedSubscription == false)
		{
			UniStrCpy(tmp, sizeof(tmp), _UU("SM_LICENSE_STATUS_SUBSCRIPTION_NONEED"));
		}
		else
		{
			if (st.SubscriptionExpires == 0)
			{
				UniStrCpy(tmp, sizeof(tmp), _UU("SM_LICENSE_STATUS_SUBSCRIPTION_NONE"));
			}
			else
			{
				wchar_t dtstr[MAX_PATH];

				GetDateStrEx64(dtstr, sizeof(dtstr), st.SubscriptionExpires, NULL);

				UniFormat(tmp, sizeof(tmp),
					st.IsSubscriptionExpired ? _UU("SM_LICENSE_STATUS_SUBSCRIPTION_EXPIRED") :  _UU("SM_LICENSE_STATUS_SUBSCRIPTION_VALID"),
					dtstr);
			}
		}
		CtInsert(ct, _UU("SM_LICENSE_STATUS_SUBSCRIPTION"), tmp);

		if (st.NeedSubscription == false && st.SubscriptionExpires != 0)
		{
			wchar_t dtstr[MAX_PATH];

			GetDateStrEx64(dtstr, sizeof(dtstr), st.SubscriptionExpires, NULL);

			CtInsert(ct, _UU("SM_LICENSE_STATUS_SUBSCRIPTION_BUILD_STR"), tmp);
		}

		if (GetCapsBool(ps->CapsList, "b_vpn3"))
		{
			// Maximum creatable number of users
			if (st.NumClientConnectLicense == INFINITE)
			{
				UniStrCpy(tmp, sizeof(tmp), _UU("SM_LICENSE_INFINITE"));
			}
			else
			{
				UniToStru(tmp, st.NumClientConnectLicense);
			}
			CtInsert(ct, _UU("SM_LICENSE_NUM_CLIENT"), tmp);
		}

		// Available number of concurrent client connections
		if (st.NumBridgeConnectLicense == INFINITE)
		{
			UniStrCpy(tmp, sizeof(tmp), _UU("SM_LICENSE_INFINITE"));
		}
		else
		{
			UniToStru(tmp, st.NumBridgeConnectLicense);
		}
		CtInsert(ct, _UU("SM_LICENSE_NUM_BRIDGE"), tmp);

		// Availability of enterprise features
		CtInsert(ct, _UU("SM_LICENSE_STATUS_ENTERPRISE"),
			st.AllowEnterpriseFunction ? _UU("SM_LICENSE_STATUS_ENTERPRISE_YES") : _UU("SM_LICENSE_STATUS_ENTERPRISE_NO"));
	}

	CtFreeEx(ct, c, false);

	FreeParamValueList(o);

	return 0;
}