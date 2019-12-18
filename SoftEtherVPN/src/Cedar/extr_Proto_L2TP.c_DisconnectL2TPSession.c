#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int Disconnecting; int WantToDisconnect; int /*<<< orphan*/  SessionId2; int /*<<< orphan*/  SessionId1; scalar_t__ Established; } ;
struct TYPE_5__ {int /*<<< orphan*/  TunnelId2; int /*<<< orphan*/  TunnelId1; } ;
typedef  TYPE_1__ L2TP_TUNNEL ;
typedef  TYPE_2__ L2TP_SESSION ;

/* Variables and functions */
 int /*<<< orphan*/  Debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void DisconnectL2TPSession(L2TP_TUNNEL *t, L2TP_SESSION *s)
{
	// Validate arguments
	if (t == NULL || s == NULL)
	{
		return;
	}

	if (s->Established && s->Disconnecting == false && s->WantToDisconnect == false)
	{
		Debug("Trying to Disconnect Session ID %u/%u on Tunnel %u/%u\n", s->SessionId1, s->SessionId2,
			t->TunnelId1, t->TunnelId2);
		s->WantToDisconnect = true;
	}
}