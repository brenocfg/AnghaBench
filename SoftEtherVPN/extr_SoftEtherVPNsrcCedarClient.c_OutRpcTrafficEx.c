#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_6__ {int /*<<< orphan*/  UnicastCount; int /*<<< orphan*/  UnicastBytes; int /*<<< orphan*/  BroadcastCount; int /*<<< orphan*/  BroadcastBytes; } ;
struct TYPE_5__ {int /*<<< orphan*/  UnicastCount; int /*<<< orphan*/  UnicastBytes; int /*<<< orphan*/  BroadcastCount; int /*<<< orphan*/  BroadcastBytes; } ;
struct TYPE_7__ {TYPE_2__ Send; TYPE_1__ Recv; } ;
typedef  TYPE_3__ TRAFFIC ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  PackAddInt64Ex (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void OutRpcTrafficEx(TRAFFIC *t, PACK *p, UINT i, UINT num)
{
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	PackAddInt64Ex(p, "Ex.Recv.BroadcastBytes", t->Recv.BroadcastBytes, i, num);
	PackAddInt64Ex(p, "Ex.Recv.BroadcastCount", t->Recv.BroadcastCount, i, num);
	PackAddInt64Ex(p, "Ex.Recv.UnicastBytes", t->Recv.UnicastBytes, i, num);
	PackAddInt64Ex(p, "Ex.Recv.UnicastCount", t->Recv.UnicastCount, i, num);
	PackAddInt64Ex(p, "Ex.Send.BroadcastBytes", t->Send.BroadcastBytes, i, num);
	PackAddInt64Ex(p, "Ex.Send.BroadcastCount", t->Send.BroadcastCount, i, num);
	PackAddInt64Ex(p, "Ex.Send.UnicastBytes", t->Send.UnicastBytes, i, num);
	PackAddInt64Ex(p, "Ex.Send.UnicastCount", t->Send.UnicastCount, i, num);
}