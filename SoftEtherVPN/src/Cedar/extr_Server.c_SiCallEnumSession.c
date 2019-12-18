#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_11__ {int /*<<< orphan*/  hostname; } ;
struct TYPE_10__ {size_t NumSession; TYPE_1__* Sessions; } ;
struct TYPE_9__ {int RemoteSession; int /*<<< orphan*/  RemoteHostname; } ;
typedef  int /*<<< orphan*/  SERVER ;
typedef  TYPE_2__ RPC_ENUM_SESSION ;
typedef  int /*<<< orphan*/  PACK ;
typedef  TYPE_3__ FARM_MEMBER ;

/* Variables and functions */
 int /*<<< orphan*/  FreePack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InRpcEnumSession (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewPack () ; 
 int /*<<< orphan*/  PackAddStr (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/ * SiCallTask (TYPE_3__*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 

void SiCallEnumSession(SERVER *s, FARM_MEMBER *f, char *hubname, RPC_ENUM_SESSION *t)
{
	PACK *p;
	UINT i;
	// Validate arguments
	if (s == NULL || f == NULL || hubname == NULL || t == NULL)
	{
		return;
	}

	p = NewPack();
	PackAddStr(p, "HubName", hubname);

	p = SiCallTask(f, p, "enumsession");

	Zero(t, sizeof(RPC_ENUM_SESSION));
	InRpcEnumSession(t, p);

	for (i = 0;i < t->NumSession;i++)
	{
		t->Sessions[i].RemoteSession = true;
		StrCpy(t->Sessions[i].RemoteHostname, sizeof(t->Sessions[i].RemoteHostname),
			f->hostname);
	}

	FreePack(p);
}