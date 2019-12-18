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
typedef  int /*<<< orphan*/  RPC_READ_LOG_FILE ;
typedef  int /*<<< orphan*/  PACK ;
typedef  int /*<<< orphan*/  FARM_MEMBER ;

/* Variables and functions */
 int /*<<< orphan*/  FreePack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeRpcReadLogFile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InRpcReadLogFile (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewPack () ; 
 int /*<<< orphan*/  OutRpcReadLogFile (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SiCallTask (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  Zero (int /*<<< orphan*/ *,int) ; 

bool SiCallReadLogFile(SERVER *s, FARM_MEMBER *f, RPC_READ_LOG_FILE *t)
{
	PACK *p;
	// Validate arguments
	if (s == NULL || f == NULL)
	{
		return false;
	}

	p = NewPack();
	OutRpcReadLogFile(p, t);
	FreeRpcReadLogFile(t);
	Zero(t, sizeof(RPC_READ_LOG_FILE));

	p = SiCallTask(f, p, "readlogfile");

	if (p == NULL)
	{
		return false;
	}

	InRpcReadLogFile(t, p);
	FreePack(p);

	return true;
}