#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {void* UnicastCount; void* UnicastBytes; void* BroadcastCount; void* BroadcastBytes; } ;
struct TYPE_6__ {void* UnicastCount; void* UnicastBytes; void* BroadcastCount; void* BroadcastBytes; } ;
struct TYPE_8__ {TYPE_2__ Send; TYPE_1__ Recv; } ;
typedef  TYPE_3__ TRAFFIC ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 void* PackGetInt64 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  Zero (TYPE_3__*,int) ; 

void InRpcTraffic(TRAFFIC *t, PACK *p)
{
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	Zero(t, sizeof(TRAFFIC));
	t->Recv.BroadcastBytes = PackGetInt64(p, "Recv.BroadcastBytes");
	t->Recv.BroadcastCount = PackGetInt64(p, "Recv.BroadcastCount");
	t->Recv.UnicastBytes = PackGetInt64(p, "Recv.UnicastBytes");
	t->Recv.UnicastCount = PackGetInt64(p, "Recv.UnicastCount");
	t->Send.BroadcastBytes = PackGetInt64(p, "Send.BroadcastBytes");
	t->Send.BroadcastCount = PackGetInt64(p, "Send.BroadcastCount");
	t->Send.UnicastBytes = PackGetInt64(p, "Send.UnicastBytes");
	t->Send.UnicastCount = PackGetInt64(p, "Send.UnicastCount");
}