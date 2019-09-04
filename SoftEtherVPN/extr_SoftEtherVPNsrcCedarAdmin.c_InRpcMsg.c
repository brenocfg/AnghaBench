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
typedef  scalar_t__ UINT ;
struct TYPE_4__ {int /*<<< orphan*/  Msg; int /*<<< orphan*/  HubName; } ;
typedef  TYPE_1__ RPC_MSG ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  CopyUtfToUni (char*) ; 
 int /*<<< orphan*/  Free (char*) ; 
 int /*<<< orphan*/  PackGetData (int /*<<< orphan*/ *,char*,char*) ; 
 scalar_t__ PackGetDataSize (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PackGetStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 
 char* ZeroMalloc (scalar_t__) ; 

void InRpcMsg(RPC_MSG *t, PACK *p)
{
	UINT size;
	char *utf8;
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	Zero(t, sizeof(RPC_MSG));

	PackGetStr(p, "HubName", t->HubName, sizeof(t->HubName));
	size = PackGetDataSize(p, "Msg");
	utf8 = ZeroMalloc(size + 8);
	PackGetData(p, "Msg", utf8);
	t->Msg = CopyUtfToUni(utf8);
	Free(utf8);
}