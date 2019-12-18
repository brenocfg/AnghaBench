#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* Write ) (TYPE_1__*,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_1__ CONSOLE ;

/* Variables and functions */
 char* CopyUniToStr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Free (char*) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * StrToPortList (char*) ; 
 int /*<<< orphan*/  _UU (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 

bool CmdEvalPortList(CONSOLE *c, wchar_t *str, void *param)
{
	char *s;
	bool ret = false;
	LIST *o;
	// Validate arguments
	if (c == NULL || str == NULL)
	{
		return false;
	}

	s = CopyUniToStr(str);

	o = StrToPortList(s);

	if (o != NULL)
	{
		ret = true;
	}

	ReleaseList(o);

	Free(s);

	if (ret == false)
	{
		c->Write(c, _UU("CMD_PORTLIST_EVAL_FAILED"));
	}

	return ret;
}