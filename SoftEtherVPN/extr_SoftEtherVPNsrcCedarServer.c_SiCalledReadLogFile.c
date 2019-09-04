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
typedef  int /*<<< orphan*/  t ;
typedef  int /*<<< orphan*/  filepath ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  SERVER ;
typedef  int /*<<< orphan*/  RPC_READ_LOG_FILE ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  FreeRpcReadLogFile (int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/ * NewPack () ; 
 int /*<<< orphan*/  OutRpcReadLogFile (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PackGetInt (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PackGetStr (int /*<<< orphan*/ *,char*,char*,int) ; 
 int /*<<< orphan*/  SiReadLocalLogFile (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Zero (int /*<<< orphan*/ *,int) ; 

PACK *SiCalledReadLogFile(SERVER *s, PACK *p)
{
	RPC_READ_LOG_FILE t;
	PACK *ret;
	char filepath[MAX_PATH];
	UINT offset;
	// Validate arguments
	if (s == NULL || p == NULL)
	{
		return NULL;
	}

	PackGetStr(p, "FilePath", filepath, sizeof(filepath));
	offset = PackGetInt(p, "Offset");

	Zero(&t, sizeof(t));

	SiReadLocalLogFile(s, filepath, offset, &t);

	ret = NewPack();

	OutRpcReadLogFile(ret, &t);
	FreeRpcReadLogFile(&t);

	return ret;
}