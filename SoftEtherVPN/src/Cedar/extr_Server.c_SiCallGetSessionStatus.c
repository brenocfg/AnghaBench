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
typedef  int /*<<< orphan*/  SERVER ;
typedef  int /*<<< orphan*/  RPC_SESSION_STATUS ;
typedef  int /*<<< orphan*/  PACK ;
typedef  int /*<<< orphan*/  FARM_MEMBER ;

/* Variables and functions */
 int /*<<< orphan*/  FreePack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeRpcSessionStatus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InRpcSessionStatus (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewPack () ; 
 int /*<<< orphan*/  OutRpcSessionStatus (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SiCallTask (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  Zero (int /*<<< orphan*/ *,int) ; 

bool SiCallGetSessionStatus(SERVER *s, FARM_MEMBER *f, RPC_SESSION_STATUS *t)
{
	PACK *p;
	// Validate arguments
	if (s == NULL || f == NULL)
	{
		return false;
	}

	p = NewPack();
	OutRpcSessionStatus(p, t);
	FreeRpcSessionStatus(t);
	Zero(t, sizeof(RPC_SESSION_STATUS));

	p = SiCallTask(f, p, "getsessionstatus");

	if (p == NULL)
	{
		return false;
	}

	InRpcSessionStatus(t, p);
	FreePack(p);

	return true;
}