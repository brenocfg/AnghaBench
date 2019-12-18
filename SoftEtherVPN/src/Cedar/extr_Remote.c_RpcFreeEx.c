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
struct TYPE_4__ {int /*<<< orphan*/  Lock; int /*<<< orphan*/  Sock; } ;
typedef  TYPE_1__ RPC ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Disconnect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  ReleaseSock (int /*<<< orphan*/ ) ; 

void RpcFreeEx(RPC *rpc, bool no_disconnect)
{
	// Validate arguments
	if (rpc == NULL)
	{
		return;
	}

	if (no_disconnect == false)
	{
		Disconnect(rpc->Sock);
	}

	ReleaseSock(rpc->Sock);

	DeleteLock(rpc->Lock);

	Free(rpc);
}