#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
struct TYPE_5__ {int DisconnectFlag; int DisconnectedByYou; int /*<<< orphan*/  Magic_Disconnect; int /*<<< orphan*/ * TcpSock; } ;
typedef  int /*<<< orphan*/  RUDP_STACK ;
typedef  TYPE_1__ RUDP_SESSION ;

/* Variables and functions */
 int /*<<< orphan*/  Debug (char*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  Disconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RUDPSendSegmentNow (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSock (int /*<<< orphan*/ *) ; 

void RUDPDisconnectSession(RUDP_STACK *r, RUDP_SESSION *se, bool disconnected_by_you)
{
	// Validate arguments
	if (r == NULL || se == NULL)
	{
		return;
	}

	if (se->DisconnectFlag == false)
	{
		UINT i;

		se->DisconnectFlag = true;
		se->DisconnectedByYou = disconnected_by_you;

		Debug("R-UDP Session %X Disconnected. by you flag: %u\n", se, disconnected_by_you);

		if (se->TcpSock != NULL)
		{
			// Disconnect a TCP socket
			Disconnect(se->TcpSock);
			ReleaseSock(se->TcpSock);

			se->TcpSock = NULL;
		}

		// Send 5 disconnect signals serially if to disconnect from here
		if (disconnected_by_you == false)
		{
			for (i = 0;i < 5;i++)
			{
				RUDPSendSegmentNow(r, se, se->Magic_Disconnect, NULL, 0);
			}
		}
	}
}