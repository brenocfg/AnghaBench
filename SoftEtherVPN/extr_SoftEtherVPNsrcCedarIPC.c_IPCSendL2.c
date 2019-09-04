#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_5__ {TYPE_1__* Sock; int /*<<< orphan*/  FlushList; } ;
struct TYPE_4__ {int /*<<< orphan*/  SendTube; } ;
typedef  TYPE_2__ IPC ;

/* Variables and functions */
 int /*<<< orphan*/  AddTubeToFlushList (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TubeSendEx (int /*<<< orphan*/ ,void*,scalar_t__,int /*<<< orphan*/ *,int) ; 

void IPCSendL2(IPC *ipc, void *data, UINT size)
{
	// Validate arguments
	if (ipc == NULL || data == NULL || size == 0)
	{
		return;
	}

	if (ipc->Sock == NULL)
	{
		return;
	}

	TubeSendEx(ipc->Sock->SendTube, data, size, NULL, true);
	AddTubeToFlushList(ipc->FlushList, ipc->Sock->SendTube);
}