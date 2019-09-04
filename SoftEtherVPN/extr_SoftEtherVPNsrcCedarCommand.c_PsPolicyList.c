#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  args ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_3__ {char* member_0; int /*<<< orphan*/ * member_4; int /*<<< orphan*/ * member_3; int /*<<< orphan*/ * member_2; int /*<<< orphan*/ * member_1; } ;
typedef  TYPE_1__ PARAM ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  CONSOLE ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  ERR_NO_ERROR ; 
 int /*<<< orphan*/  FreeParamValueList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetParamStr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * ParseCommandList (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  PrintPolicyList (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

UINT PsPolicyList(CONSOLE *c, char *cmd_name, wchar_t *str, void *param)
{
	LIST *o;
	PARAM args[] =
	{
		// "name", prompt_proc, prompt_param, eval_proc, eval_param
		{"[name]", NULL, NULL, NULL, NULL}
	};

	o = ParseCommandList(c, cmd_name, str, args, sizeof(args) / sizeof(args[0]));
	if (o == NULL)
	{
		return ERR_INVALID_PARAMETER;
	}

	PrintPolicyList(c, GetParamStr(o, "[name]"));

	FreeParamValueList(o);

	return ERR_NO_ERROR;
}