#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  result ;
typedef  int /*<<< orphan*/  args ;
typedef  unsigned long long UINT64 ;
typedef  scalar_t__ UINT ;
struct TYPE_16__ {char* member_0; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; } ;
struct TYPE_15__ {scalar_t__ ConsoleType; int /*<<< orphan*/ * Param; int /*<<< orphan*/  (* Write ) (TYPE_3__*,int /*<<< orphan*/ *) ;} ;
struct TYPE_14__ {int /*<<< orphan*/ * InBuf; } ;
struct TYPE_13__ {char* member_0; TYPE_4__* member_4; int /*<<< orphan*/ * member_3; int /*<<< orphan*/ * member_2; int /*<<< orphan*/ * member_1; } ;
typedef  int /*<<< orphan*/  TT_RESULT ;
typedef  int /*<<< orphan*/  TTC ;
typedef  TYPE_1__ PARAM ;
typedef  TYPE_2__ LOCAL_CONSOLE_PARAM ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_3__ CONSOLE ;
typedef  TYPE_4__ CMD_EVAL_MIN_MAX ;

/* Variables and functions */
 scalar_t__ CONSOLE_LOCAL ; 
 int /*<<< orphan*/ * CmdEvalMinMax ; 
 int /*<<< orphan*/ * CmdEvalNotEmpty ; 
 int /*<<< orphan*/  CmdPrintError (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/ * CmdPrompt ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_NO_ERROR ; 
 int /*<<< orphan*/  Free (char*) ; 
 int /*<<< orphan*/  FreeParamValueList (int /*<<< orphan*/ *) ; 
 scalar_t__ FreeTtc (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ GetParamInt (int /*<<< orphan*/ *,char*) ; 
 char* GetParamStr (int /*<<< orphan*/ *,char*) ; 
 int GetParamYes (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * NewTtc (char*,scalar_t__,scalar_t__,scalar_t__,unsigned long long,int,int,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/ * ParseCommandList (TYPE_3__*,char*,int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int ParseHostPort (char*,char**,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PtTrafficPrintProc ; 
 scalar_t__ StartWith (char*,char*) ; 
 int /*<<< orphan*/  TRAFFIC_DEFAULT_PORT ; 
 scalar_t__ TRAFFIC_NUMTCP_DEFAULT ; 
 int /*<<< orphan*/  TRAFFIC_NUMTCP_MAX ; 
 scalar_t__ TRAFFIC_SPAN_DEFAULT ; 
 scalar_t__ TRAFFIC_TYPE_DOWNLOAD ; 
 scalar_t__ TRAFFIC_TYPE_FULL ; 
 scalar_t__ TRAFFIC_TYPE_UPLOAD ; 
 int /*<<< orphan*/  Trim (char*) ; 
 int /*<<< orphan*/  TtcPrintResult (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Zero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * _UU (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*,int /*<<< orphan*/ *) ; 

UINT PtTrafficClient(CONSOLE *c, char *cmd_name, wchar_t *str, void *param)
{
	TTC *ttc;
	LIST *o;
	UINT ret = ERR_NO_ERROR;
	char *host = NULL;
	UINT port;
	UINT num, type;
	bool dbl = false, raw = false;
	UINT64 span;
	// Parameter list that can be specified
	CMD_EVAL_MIN_MAX minmax =
	{
		"CMD_TrafficClient_EVAL_NUMTCP",
		0, TRAFFIC_NUMTCP_MAX,
	};
	PARAM args[] =
	{
		{"[host:port]", CmdPrompt, _UU("CMD_TrafficClient_PROMPT_HOST"), CmdEvalNotEmpty, NULL},
		{"NUMTCP", NULL, NULL, CmdEvalMinMax, &minmax},
		{"TYPE", NULL, NULL, NULL, NULL},
		{"SPAN", NULL, NULL, NULL, NULL},
		{"DOUBLE", NULL, NULL, NULL, NULL},
		{"RAW", NULL, NULL, NULL, NULL},
	};

	// Get the parameter list
	o = ParseCommandList(c, cmd_name, str, args, sizeof(args) / sizeof(args[0]));
	if (o == NULL)
	{
		return ERR_INVALID_PARAMETER;
	}

	if (ParseHostPort(GetParamStr(o, "[host:port]"), &host, &port, TRAFFIC_DEFAULT_PORT) == false)
	{
		c->Write(c, _UU("CMD_TrafficClient_ERROR_HOSTPORT"));
		ret = ERR_INVALID_PARAMETER;
	}
	else
	{
		char *s;
		UINT i;

		Trim(host);

		num = GetParamInt(o, "NUMTCP");
		if (num == 0)
		{
			num = TRAFFIC_NUMTCP_DEFAULT;
		}
		s = GetParamStr(o, "TYPE");

		if (StartWith("download", s))
		{
			type = TRAFFIC_TYPE_DOWNLOAD;
		}
		else if (StartWith("upload", s))
		{
			type = TRAFFIC_TYPE_UPLOAD;
		}
		else
		{
			type = TRAFFIC_TYPE_FULL;
		}

		i = GetParamInt(o, "SPAN");

		if (i == 0)
		{
			i = TRAFFIC_SPAN_DEFAULT;
		}

		span = (UINT64)i * 1000ULL;

		dbl = GetParamYes(o, "DOUBLE");
		raw = GetParamYes(o, "RAW");

		if (type == TRAFFIC_TYPE_FULL)
		{
			if ((num % 2) != 0)
			{
				ret = ERR_INVALID_PARAMETER;
				c->Write(c, _UU("CMD_TrafficClient_ERROR_NUMTCP"));
			}
		}

		if (ret == ERR_NO_ERROR)
		{
			TT_RESULT result;
			ttc = NewTtc(host, port, num, type, span, dbl, raw, PtTrafficPrintProc, c);

			if (c->ConsoleType == CONSOLE_LOCAL)
			{
				if (c->Param != NULL && (((LOCAL_CONSOLE_PARAM *)c->Param)->InBuf == NULL))
				{
//					c->Write(c, _UU("TTC_ENTER_TO_EXIT"));
//					GetLine(NULL, 0);
//					StopTtc(ttc);
				}
			}


			Zero(&result, sizeof(result));
			ret = FreeTtc(ttc, &result);

			if (ret == ERR_NO_ERROR)
			{
				TtcPrintResult(c, &result);
			}
		}
	}

	if (ret != ERR_NO_ERROR)
	{
		CmdPrintError(c, ret);
	}

	// Release of the parameter list
	FreeParamValueList(o);

	Free(host);

	return ret;
}