#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_14__ {int IgnoreRecvErr; int /*<<< orphan*/  LocalPort; } ;
struct TYPE_13__ {TYPE_1__* Server; } ;
struct TYPE_12__ {TYPE_4__* Sock; TYPE_3__* Cedar; scalar_t__ Halt; int /*<<< orphan*/  Status; int /*<<< orphan*/  Event; int /*<<< orphan*/  Port; } ;
struct TYPE_11__ {int /*<<< orphan*/  ListenIP; } ;
typedef  int /*<<< orphan*/  SOCKSET ;
typedef  TYPE_2__ LISTENER ;
typedef  int /*<<< orphan*/  IP ;

/* Variables and functions */
 int /*<<< orphan*/  AddSockSet (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  Debug (char*,...) ; 
 int /*<<< orphan*/  Disconnect (TYPE_4__*) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InitSockSet (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LISTENER_STATUS_LISTENING ; 
 int /*<<< orphan*/  LISTENER_STATUS_TRYING ; 
 int /*<<< orphan*/  LISTEN_RETRY_TIME ; 
 int /*<<< orphan*/ * Malloc (int /*<<< orphan*/ ) ; 
 TYPE_4__* NewUDPEx2 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ RecvFrom (TYPE_4__*,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSock (TYPE_4__*) ; 
 int /*<<< orphan*/  SELECT_TIME ; 
 scalar_t__ SOCK_LATER ; 
 int /*<<< orphan*/  Select (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UDPReceivedPacket (TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  UDP_PACKET_SIZE ; 
 int /*<<< orphan*/  Wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ListenerUDPMainLoop(LISTENER *r)
{
	UCHAR *data;
	// Validate arguments
	if (r == NULL)
	{
		return;
	}

	Debug("ListenerUDPMainLoop Starts.\n");
	r->Status = LISTENER_STATUS_TRYING;

	while (true)
	{
		// Try to listen on the UDP port
		while (true)
		{
			// Stop flag inspection
			if (r->Halt)
			{
				// Stop
				return;
			}

			Debug("NewUDP()\n");
			r->Sock = NewUDPEx2(r->Port, false, &r->Cedar->Server->ListenIP);
			if (r->Sock != NULL)
			{
				// Wait success
				break;
			}

			// Wait failure
			Debug("Failed to NewUDP.\n");
			Wait(r->Event, LISTEN_RETRY_TIME);

			// Stop flag inspection
			if (r->Halt)
			{
				Debug("UDP Halt.\n");
				return;
			}
		}

		r->Status = LISTENER_STATUS_LISTENING;
		Debug("Start Listening at UDP Port %u.\n", r->Sock->LocalPort);

		// Stop flag inspection
		if (r->Halt)
		{
			// Stop
			goto STOP;
		}

		// Allocate the buffer area
		data = Malloc(UDP_PACKET_SIZE);

		// Read the next packet
		while (true)
		{
			IP src_ip;
			UINT src_port;
			UINT size;
			SOCKSET set;

			InitSockSet(&set);
			AddSockSet(&set, r->Sock);
			Select(&set, SELECT_TIME, NULL, NULL);

			size = RecvFrom(r->Sock, &src_ip, &src_port, data, UDP_PACKET_SIZE);
			if (((size == 0) && (r->Sock->IgnoreRecvErr == false)) || r->Halt)
			{
				// Error has occurred
STOP:
				Disconnect(r->Sock);
				ReleaseSock(r->Sock);
				r->Sock = NULL;
				Debug("UDP Listen Stopped.\n");
				Free(data);
				break;
			}

			// Received an UDP packet
			if (size != SOCK_LATER)
			{
				UDPReceivedPacket(r->Cedar, r->Sock, &src_ip, src_port, data, size);
			}
		}
	}
}