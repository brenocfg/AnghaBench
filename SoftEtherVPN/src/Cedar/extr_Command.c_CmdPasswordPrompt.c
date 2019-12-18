#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {char* (* ReadPassword ) (TYPE_1__*,char*) ;int /*<<< orphan*/  (* Write ) (TYPE_1__*,char*) ;} ;
typedef  TYPE_1__ CONSOLE ;

/* Variables and functions */
 int /*<<< orphan*/  Free (char*) ; 
 scalar_t__ StrCmp (char*,char*) ; 
 char* _UU (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,char*) ; 
 char* stub3 (TYPE_1__*,char*) ; 
 char* stub4 (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  stub5 (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  stub6 (TYPE_1__*,char*) ; 

char *CmdPasswordPrompt(CONSOLE *c)
{
	char *pw1, *pw2;
	// Validate arguments
	if (c == NULL)
	{
		return NULL;
	}

	c->Write(c, _UU("CMD_VPNCMD_PWPROMPT_0"));

RETRY:
	c->Write(c, L"");


	pw1 = c->ReadPassword(c, _UU("CMD_VPNCMD_PWPROMPT_1"));
	if (pw1 == NULL)
	{
		return NULL;
	}

	pw2 = c->ReadPassword(c, _UU("CMD_VPNCMD_PWPROMPT_2"));
	if (pw2 == NULL)
	{
		Free(pw1);
		return NULL;
	}

	c->Write(c, L"");

	if (StrCmp(pw1, pw2) != 0)
	{
		Free(pw1);
		Free(pw2);
		c->Write(c, _UU("CMD_VPNCMD_PWPROMPT_3"));
		goto RETRY;
	}

	Free(pw1);

	return pw2;
}