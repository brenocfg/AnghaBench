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
typedef  int /*<<< orphan*/  t ;
typedef  int /*<<< orphan*/  args ;
typedef  scalar_t__ UINT ;
struct TYPE_9__ {char* member_0; int /*<<< orphan*/ * member_4; int /*<<< orphan*/ * member_3; int /*<<< orphan*/ * member_2; int /*<<< orphan*/ * member_1; } ;
struct TYPE_8__ {int /*<<< orphan*/  Rpc; } ;
struct TYPE_7__ {int /*<<< orphan*/  ControllerOnly; scalar_t__ Weight; int /*<<< orphan*/  ServerType; } ;
typedef  TYPE_1__ RPC_FARM ;
typedef  TYPE_2__ PS ;
typedef  TYPE_3__ PARAM ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  CONSOLE ;

/* Variables and functions */
 int /*<<< orphan*/  CmdPrintError (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_NO_ERROR ; 
 scalar_t__ FARM_DEFAULT_WEIGHT ; 
 int /*<<< orphan*/  FreeParamValueList (int /*<<< orphan*/ *) ; 
 scalar_t__ GetParamInt (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  GetParamYes (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * ParseCommandList (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 int /*<<< orphan*/  SERVER_TYPE_FARM_CONTROLLER ; 
 scalar_t__ ScSetFarmSetting (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

UINT PsClusterSettingController(CONSOLE *c, char *cmd_name, wchar_t *str, void *param)
{
	LIST *o;
	PS *ps = (PS *)param;
	UINT ret = 0;
	RPC_FARM t;
	UINT weight;
	PARAM args[] =
	{
		{"WEIGHT", NULL, NULL, NULL, NULL},
		{"ONLY", NULL, NULL, NULL, NULL},
	};

	o = ParseCommandList(c, cmd_name, str, args, sizeof(args) / sizeof(args[0]));
	if (o == NULL)
	{
		return ERR_INVALID_PARAMETER;
	}

	weight = GetParamInt(o, "WEIGHT");
	if (weight == 0)
	{
		weight = FARM_DEFAULT_WEIGHT;
	}

	Zero(&t, sizeof(t));
	t.ServerType = SERVER_TYPE_FARM_CONTROLLER;
	t.Weight = weight;
	t.ControllerOnly = GetParamYes(o, "ONLY");

	// RPC call
	ret = ScSetFarmSetting(ps->Rpc, &t);

	if (ret != ERR_NO_ERROR)
	{
		// An error has occured
		CmdPrintError(c, ret);
		FreeParamValueList(o);
		return ret;
	}

	FreeParamValueList(o);

	return 0;
}