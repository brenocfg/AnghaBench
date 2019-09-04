#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  SOCK ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/ * CncConnect () ; 
 int /*<<< orphan*/  Disconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreePack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewPack () ; 
 int /*<<< orphan*/  PackAddStr (int /*<<< orphan*/ *,char*,char*) ; 
 int PackGetBool (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * RecvPack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseSock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SendPack (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

bool CncExecDriverInstaller(char *arg)
{
	SOCK *s = CncConnect();
	PACK *p;
	bool ret;
	if (s == NULL)
	{
		return false;
	}

	p = NewPack();
	PackAddStr(p, "function", "exec_driver_installer");
	PackAddStr(p, "arg", arg);

	SendPack(s, p);
	FreePack(p);

	p = RecvPack(s);
	if (p == NULL)
	{
		Disconnect(s);
		ReleaseSock(s);
		return false;
	}

	ret = PackGetBool(p, "ret");

	FreePack(p);

	Disconnect(s);
	ReleaseSock(s);

	return ret;
}