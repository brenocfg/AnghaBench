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
struct TYPE_4__ {int Disconnecting; int WantToDisconnect; int /*<<< orphan*/  SessionList; int /*<<< orphan*/  TunnelId2; int /*<<< orphan*/  TunnelId1; } ;
typedef  TYPE_1__ L2TP_TUNNEL ;
typedef  int /*<<< orphan*/  L2TP_SESSION ;

/* Variables and functions */
 int /*<<< orphan*/  Debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DisconnectL2TPSession (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 

void DisconnectL2TPTunnel(L2TP_TUNNEL *t)
{
	// Validate arguments
	if (t == NULL)
	{
		return;
	}

	if (/*t->Established && */t->Disconnecting == false && t->WantToDisconnect == false)
	{
		UINT i;

		Debug("Trying to Disconnect Tunnel ID %u/%u\n", t->TunnelId1, t->TunnelId2);
		t->WantToDisconnect = true;

		// Disconnect all sessions within the tunnel
		for (i = 0;i < LIST_NUM(t->SessionList);i++)
		{
			L2TP_SESSION *s = LIST_DATA(t->SessionList, i);

			DisconnectL2TPSession(t, s);
		}
	}
}