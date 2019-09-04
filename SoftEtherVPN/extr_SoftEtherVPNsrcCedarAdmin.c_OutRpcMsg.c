#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_3__ {int /*<<< orphan*/  Msg; int /*<<< orphan*/  HubName; } ;
typedef  TYPE_1__ RPC_MSG ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 char* CopyUniToUtf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (char*) ; 
 int /*<<< orphan*/  PackAddData (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrLen (char*) ; 

void OutRpcMsg(PACK *p, RPC_MSG *t)
{
	UINT size;
	char *utf8;
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	PackAddStr(p, "HubName", t->HubName);
	utf8 = CopyUniToUtf(t->Msg);
	size = StrLen(utf8);
	PackAddData(p, "Msg", utf8, size);
	Free(utf8);
}