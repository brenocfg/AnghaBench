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
 int /*<<< orphan*/  MsGetProcessId () ; 
 int /*<<< orphan*/ * NewPack () ; 
 int /*<<< orphan*/  PackAddInt (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddStr (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  ReleaseSock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SendPack (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void CncReleaseSocket()
{
	SOCK *s = CncConnect();
	PACK *p;
	if (s == NULL)
	{
		return;
	}

	p = NewPack();
	PackAddStr(p, "function", "release_socket");

#ifdef OS_WIN32
	PackAddInt(p, "pid", MsGetProcessId());
#endif	// OS_WIN32

	SendPack(s, p);
	FreePack(p);

	Disconnect(s);
	ReleaseSock(s);
}