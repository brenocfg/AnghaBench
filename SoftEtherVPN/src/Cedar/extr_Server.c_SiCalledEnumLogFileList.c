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
typedef  int /*<<< orphan*/  hubname ;
typedef  int /*<<< orphan*/  SERVER ;
typedef  int /*<<< orphan*/  RPC_ENUM_LOG_FILE ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  FreeRpcEnumLogFile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAX_HUBNAME_LEN ; 
 int /*<<< orphan*/ * NewPack () ; 
 int /*<<< orphan*/  OutRpcEnumLogFile (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PackGetStr (int /*<<< orphan*/ *,char*,char*,int) ; 
 int /*<<< orphan*/  SiEnumLocalLogFileList (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Zero (int /*<<< orphan*/ *,int) ; 

PACK *SiCalledEnumLogFileList(SERVER *s, PACK *p)
{
	RPC_ENUM_LOG_FILE t;
	PACK *ret;
	char hubname[MAX_HUBNAME_LEN + 1];
	// Validate arguments
	if (s == NULL || p == NULL)
	{
		return NULL;
	}

	PackGetStr(p, "HubName", hubname, sizeof(hubname));

	Zero(&t, sizeof(t));

	SiEnumLocalLogFileList(s, hubname, &t);

	ret = NewPack();

	OutRpcEnumLogFile(ret, &t);
	FreeRpcEnumLogFile(&t);

	return ret;
}