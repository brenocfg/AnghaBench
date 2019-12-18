#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  tmp ;
typedef  scalar_t__ UINT ;
struct TYPE_5__ {int /*<<< orphan*/  (* Write ) (TYPE_1__*,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ CONSOLE ;

/* Variables and functions */
 scalar_t__ ERR_DISCONNECTED ; 
 int /*<<< orphan*/  GetUniErrorStr (scalar_t__) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  UniFormat (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * _UU (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int /*<<< orphan*/ *) ; 

void CmdPrintError(CONSOLE *c, UINT err)
{
	wchar_t tmp[MAX_SIZE];
	// Validate arguments
	if (c == NULL)
	{
		return;
	}

	UniFormat(tmp, sizeof(tmp), _UU("CMD_VPNCMD_ERROR"),
		err, GetUniErrorStr(err));
	c->Write(c, tmp);

	if (err == ERR_DISCONNECTED)
	{
		c->Write(c, _UU("CMD_DISCONNECTED_MSG"));
	}
}