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
struct TYPE_3__ {int /*<<< orphan*/  IPv4ReceivedQueue; } ;
typedef  TYPE_1__ IPC ;
typedef  int /*<<< orphan*/  BLOCK ;

/* Variables and functions */
 int /*<<< orphan*/ * GetNext (int /*<<< orphan*/ ) ; 

BLOCK *IPCRecvIPv4(IPC *ipc)
{
	BLOCK *b;
	// Validate arguments
	if (ipc == NULL)
	{
		return NULL;
	}

	b = GetNext(ipc->IPv4ReceivedQueue);

	return b;
}