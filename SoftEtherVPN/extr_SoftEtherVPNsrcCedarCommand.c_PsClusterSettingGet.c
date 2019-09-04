#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ wchar_t ;
typedef  int /*<<< orphan*/  tmp2 ;
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  t ;
typedef  scalar_t__ UINT ;
struct TYPE_7__ {int /*<<< orphan*/  Rpc; } ;
struct TYPE_6__ {scalar_t__ Weight; scalar_t__ ServerType; scalar_t__ NumPort; int /*<<< orphan*/  ControllerPort; int /*<<< orphan*/  ControllerName; int /*<<< orphan*/ * Ports; int /*<<< orphan*/  PublicIp; scalar_t__ ControllerOnly; } ;
typedef  TYPE_1__ RPC_FARM ;
typedef  TYPE_2__ PS ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  CT ;
typedef  int /*<<< orphan*/  CONSOLE ;

/* Variables and functions */
 int /*<<< orphan*/  CmdPrintError (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  CtFree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CtInsert (int /*<<< orphan*/ *,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/ * CtNewStandard () ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_NO_ERROR ; 
 scalar_t__ FARM_DEFAULT_WEIGHT ; 
 int /*<<< orphan*/  FreeParamValueList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeRpcFarm (TYPE_1__*) ; 
 scalar_t__* GetServerTypeStr (scalar_t__) ; 
 int /*<<< orphan*/  IPToUniStr32 (scalar_t__*,int,int /*<<< orphan*/ ) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/ * ParseCommandList (int /*<<< orphan*/ *,char*,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ SERVER_TYPE_FARM_CONTROLLER ; 
 scalar_t__ SERVER_TYPE_FARM_MEMBER ; 
 scalar_t__ SERVER_TYPE_STANDALONE ; 
 scalar_t__ ScGetFarmSetting (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ UniEndWith (scalar_t__*,char*) ; 
 int /*<<< orphan*/  UniFormat (scalar_t__*,int,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  UniStrCat (scalar_t__*,int,scalar_t__*) ; 
 int /*<<< orphan*/  UniStrCpy (scalar_t__*,int,scalar_t__*) ; 
 int UniStrLen (scalar_t__*) ; 
 int /*<<< orphan*/  UniToStru (scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 
 scalar_t__* _UU (char*) ; 

UINT PsClusterSettingGet(CONSOLE *c, char *cmd_name, wchar_t *str, void *param)
{
	LIST *o;
	PS *ps = (PS *)param;
	UINT ret;
	RPC_FARM t;
	CT *ct;

	o = ParseCommandList(c, cmd_name, str, NULL, 0);
	if (o == NULL)
	{
		return ERR_INVALID_PARAMETER;
	}

	Zero(&t, sizeof(t));

	ret = ScGetFarmSetting(ps->Rpc, &t);

	if (ret != ERR_NO_ERROR)
	{
		CmdPrintError(c, ret);
		FreeParamValueList(o);
		return ret;
	}

	if (t.Weight == 0)
	{
		t.Weight = FARM_DEFAULT_WEIGHT;
	}

	// Show the cluster configuration
	ct = CtNewStandard();

	CtInsert(ct, _UU("CMD_ClusterSettingGet_Current"),
		GetServerTypeStr(t.ServerType));

	if (t.ServerType == SERVER_TYPE_FARM_CONTROLLER)
	{
		CtInsert(ct, _UU("CMD_ClusterSettingGet_ControllerOnly"), t.ControllerOnly ? _UU("SEC_YES") : _UU("SEC_NO"));
	}

	if (t.ServerType != SERVER_TYPE_STANDALONE)
	{
		wchar_t tmp[MAX_SIZE];

		UniToStru(tmp, t.Weight);

		CtInsert(ct, _UU("CMD_ClusterSettingGet_Weight"), tmp);
	}

	if (t.ServerType == SERVER_TYPE_FARM_MEMBER)
	{
		wchar_t tmp[MAX_SIZE];
		UINT i;

		// Public IP address
		if (t.PublicIp != 0)
		{
			IPToUniStr32(tmp, sizeof(tmp), t.PublicIp);
		}
		else
		{
			UniStrCpy(tmp, sizeof(tmp), _UU("CMD_ClusterSettingGet_None"));
		}

		CtInsert(ct, _UU("CMD_ClusterSettingGet_PublicIp"), tmp);

		// Public port list
		tmp[0] = 0;
		for (i = 0;i < t.NumPort;i++)
		{
			wchar_t tmp2[64];

			UniFormat(tmp2, sizeof(tmp2), L"%u, ", t.Ports[i]);

			UniStrCat(tmp, sizeof(tmp), tmp2);
		}

		if (UniEndWith(tmp, L", "))
		{
			tmp[UniStrLen(tmp) - 2] = 0;
		}

		CtInsert(ct, _UU("CMD_ClusterSettingGet_PublicPorts"), tmp);

		// Controller to connect
		UniFormat(tmp, sizeof(tmp), L"%S:%u", t.ControllerName, t.ControllerPort);
		CtInsert(ct, _UU("CMD_ClusterSettingGet_Controller"), tmp);
	}

	CtFree(ct, c);

	FreeRpcFarm(&t);
	FreeParamValueList(o);

	return 0;
}