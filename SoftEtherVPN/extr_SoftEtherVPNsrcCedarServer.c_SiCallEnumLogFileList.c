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
typedef  int /*<<< orphan*/  RPC_ENUM_LOG_FILE ;
typedef  int /*<<< orphan*/  PACK ;
typedef  int /*<<< orphan*/  FARM_MEMBER ;

/* Variables and functions */
 int /*<<< orphan*/  FreePack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeRpcEnumLogFile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InRpcEnumLogFile (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewPack () ; 
 int /*<<< orphan*/  OutRpcEnumLogFile (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PackAddStr (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/ * SiCallTask (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  Zero (int /*<<< orphan*/ *,int) ; 

bool SiCallEnumLogFileList(SERVER *s, FARM_MEMBER *f, RPC_ENUM_LOG_FILE *t, char *hubname)
{
	PACK *p;
	// Validate arguments
	if (s == NULL || f == NULL)
	{
		return false;
	}

	p = NewPack();
	OutRpcEnumLogFile(p, t);
	FreeRpcEnumLogFile(t);
	Zero(t, sizeof(RPC_ENUM_LOG_FILE));

	PackAddStr(p, "HubName", hubname);

	p = SiCallTask(f, p, "enumlogfilelist");

	if (p == NULL)
	{
		return false;
	}

	InRpcEnumLogFile(t, p);
	FreePack(p);

	return true;
}