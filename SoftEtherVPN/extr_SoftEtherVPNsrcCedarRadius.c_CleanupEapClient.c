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
struct TYPE_4__ {int /*<<< orphan*/  PEAP_CurrentReceivingMsg; int /*<<< orphan*/  SslPipe; int /*<<< orphan*/  UdpSock; } ;
typedef  TYPE_1__ EAP_CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  Disconnect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeSslPipe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSock (int /*<<< orphan*/ ) ; 

void CleanupEapClient(EAP_CLIENT *e)
{
	if (e == NULL)
	{
		return;
	}

	Disconnect(e->UdpSock);
	ReleaseSock(e->UdpSock);

	FreeSslPipe(e->SslPipe);

	FreeBuf(e->PEAP_CurrentReceivingMsg);

	Free(e);
}