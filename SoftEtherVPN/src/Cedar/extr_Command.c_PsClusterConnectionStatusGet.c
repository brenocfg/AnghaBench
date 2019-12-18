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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  t ;
typedef  int /*<<< orphan*/  str ;
typedef  scalar_t__ UINT ;
struct TYPE_6__ {int /*<<< orphan*/  Rpc; } ;
struct TYPE_5__ {int Online; int /*<<< orphan*/  NumFailed; int /*<<< orphan*/  NumConnected; int /*<<< orphan*/  NumTry; int /*<<< orphan*/  CurrentConnectedTime; int /*<<< orphan*/  FirstConnectedTime; int /*<<< orphan*/  StartedTime; int /*<<< orphan*/  LastError; int /*<<< orphan*/  Port; int /*<<< orphan*/  Ip; } ;
typedef  TYPE_1__ RPC_FARM_CONNECTION_STATUS ;
typedef  TYPE_2__ PS ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  CT ;
typedef  int /*<<< orphan*/  CONSOLE ;

/* Variables and functions */
 int /*<<< orphan*/  CmdPrintError (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  CtFree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CtInsert (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CtNewStandard () ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_NO_ERROR ; 
 int /*<<< orphan*/  FreeParamValueList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetDateTimeStrEx64 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPToStr32 (char*,int,int /*<<< orphan*/ ) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/ * ParseCommandList (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ScGetFarmConnectionStatus (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  StrToUni (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  SystemToLocal64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UniFormat (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UniToStru (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  _E (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * _UU (char*) ; 

UINT PsClusterConnectionStatusGet(CONSOLE *c, char *cmd_name, wchar_t *str, void *param)
{
	LIST *o;
	PS *ps = (PS *)param;
	UINT ret = 0;
	RPC_FARM_CONNECTION_STATUS t;
	wchar_t tmp[MAX_SIZE];

	o = ParseCommandList(c, cmd_name, str, NULL, 0);
	if (o == NULL)
	{
		return ERR_INVALID_PARAMETER;
	}

	Zero(&t, sizeof(t));

	// RPC call
	ret = ScGetFarmConnectionStatus(ps->Rpc, &t);

	if (ret != ERR_NO_ERROR)
	{
		// An error has occured
		CmdPrintError(c, ret);
		FreeParamValueList(o);
		return ret;
	}
	else
	{
		CT *ct = CtNewStandard();
		char str[MAX_SIZE];

		if (t.Online == false)
		{
			CtInsert(ct, _UU("SM_FC_IP"), _UU("SM_FC_NOT_CONNECTED"));

			CtInsert(ct, _UU("SM_FC_PORT"), _UU("SM_FC_NOT_CONNECTED"));
		}
		else
		{
			IPToStr32(str, sizeof(str), t.Ip);
			StrToUni(tmp, sizeof(tmp), str);
			CtInsert(ct, _UU("SM_FC_IP"), tmp);

			UniToStru(tmp, t.Port);
			CtInsert(ct, _UU("SM_FC_PORT"), tmp);
		}

		CtInsert(ct,
			_UU("SM_FC_STATUS"),
			t.Online ? _UU("SM_FC_ONLINE") : _UU("SM_FC_OFFLINE"));

		if (t.Online == false)
		{
			UniFormat(tmp, sizeof(tmp), _UU("SM_FC_ERROR_TAG"), _E(t.LastError), t.LastError);
			CtInsert(ct,
				_UU("SM_FC_LAST_ERROR"), tmp);
		}

		GetDateTimeStrEx64(tmp, sizeof(tmp), SystemToLocal64(t.StartedTime), NULL);
		CtInsert(ct, _UU("SM_FC_START_TIME"), tmp);

		GetDateTimeStrEx64(tmp, sizeof(tmp), SystemToLocal64(t.FirstConnectedTime), NULL);
		CtInsert(ct, _UU("SM_FC_FIRST_TIME"), tmp);

		//if (t.Online == false)
		{
			GetDateTimeStrEx64(tmp, sizeof(tmp), SystemToLocal64(t.CurrentConnectedTime), NULL);
			CtInsert(ct, _UU("SM_FC_CURRENT_TIME"), tmp);
		}

		UniToStru(tmp, t.NumTry);
		CtInsert(ct, _UU("SM_FC_NUM_TRY"), tmp);

		UniToStru(tmp, t.NumConnected);
		CtInsert(ct, _UU("SM_FC_NUM_CONNECTED"), tmp);

		UniToStru(tmp, t.NumFailed);
		CtInsert(ct, _UU("SM_FC_NUM_FAILED"), tmp);

		CtFree(ct, c);
	}

	FreeParamValueList(o);

	return 0;
}