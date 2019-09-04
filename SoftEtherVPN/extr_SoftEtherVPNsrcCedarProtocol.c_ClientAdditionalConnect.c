#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT64 ;
typedef  scalar_t__ UINT ;
struct TYPE_16__ {int ServerMode; int /*<<< orphan*/  ConnectingSocks; TYPE_3__* Session; int /*<<< orphan*/  CurrentNumConnection; TYPE_2__* Tcp; scalar_t__ Halt; } ;
struct TYPE_15__ {scalar_t__ Direction; scalar_t__ DisconnectTick; } ;
struct TYPE_14__ {int SessionTimeOuted; int /*<<< orphan*/  Cancel1; scalar_t__ HalfConnection; TYPE_1__* ClientOption; } ;
struct TYPE_13__ {int /*<<< orphan*/  TcpSockList; } ;
struct TYPE_12__ {int ConnectionDisconnectSpan; } ;
typedef  int /*<<< orphan*/  THREAD ;
typedef  TYPE_4__ TCPSOCK ;
typedef  int /*<<< orphan*/  SOCK ;
typedef  int /*<<< orphan*/  PACK ;
typedef  TYPE_5__ CONNECTION ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  Cancel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ClientAdditionalConnectToServer (TYPE_5__*) ; 
 int ClientDownloadHello (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int ClientUploadAuth2 (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int ClientUploadSignature (int /*<<< orphan*/ *) ; 
 char* Count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Debug (char*,...) ; 
 scalar_t__ Delete (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Disconnect (int /*<<< orphan*/ *) ; 
 scalar_t__ ERR_INVALID_PROTOCOL ; 
 scalar_t__ ERR_SESSION_TIMEOUT ; 
 int /*<<< orphan*/  FreePack (int /*<<< orphan*/ *) ; 
 scalar_t__ GetErrorFromPack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * HttpClientRecv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 TYPE_4__* NewTcpSock (int /*<<< orphan*/ *) ; 
 scalar_t__ PackGetInt (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ReleaseSock (int /*<<< orphan*/ *) ; 
 scalar_t__ TCP_SERVER_TO_CLIENT ; 
 scalar_t__ Tick64 () ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 

bool ClientAdditionalConnect(CONNECTION *c, THREAD *t)
{
	SOCK *s;
	PACK *p;
	TCPSOCK *ts;
	UINT err;
	UINT direction;

	// Validate arguments
	if (c == NULL)
	{
		return false;
	}

	// Socket connection to the server
	s = ClientAdditionalConnectToServer(c);
	if (s == NULL)
	{
		// Failed to connect socket
		return false;
	}

	if (c->Halt)
	{
		goto CLEANUP;
	}

	// Send a signature
	Debug("Uploading Signature...\n");
	if (ClientUploadSignature(s) == false)
	{
		goto CLEANUP;
	}

	if (c->Halt)
	{
		// Stop
		goto CLEANUP;
	}

	// Receive a Hello packet
	Debug("Downloading Hello...\n");
	if (ClientDownloadHello(c, s) == false)
	{
		goto CLEANUP;
	}

	if (c->Halt)
	{
		// Stop
		goto CLEANUP;
	}

	// Send a authentication data for the additional connection
	if (ClientUploadAuth2(c, s) == false)
	{
		// Disconnected
		goto CLEANUP;
	}

	// Receive a response
	p = HttpClientRecv(s);
	if (p == NULL)
	{
		// Disconnected
		goto CLEANUP;
	}

	err = GetErrorFromPack(p);
	direction = PackGetInt(p, "direction");

	FreePack(p);
	p = NULL;

	if (err != 0)
	{
		// Error has occurred
		Debug("Additional Connect Error: %u\n", err);
		if (err == ERR_SESSION_TIMEOUT || err == ERR_INVALID_PROTOCOL)
		{
			// We shall re-connection because it is a fatal error
			c->Session->SessionTimeOuted = true;
		}
		goto CLEANUP;
	}

	Debug("Additional Connect Succeed!\n");

	// Success the additional connection
	// Add to the TcpSockList of the connection
	ts = NewTcpSock(s);

	if (c->ServerMode == false)
	{
		if (c->Session->ClientOption->ConnectionDisconnectSpan != 0)
		{
			ts->DisconnectTick = Tick64() + c->Session->ClientOption->ConnectionDisconnectSpan * (UINT64)1000;
		}
	}

	LockList(c->Tcp->TcpSockList);
	{
		ts->Direction = direction;
		Add(c->Tcp->TcpSockList, ts);
	}
	UnlockList(c->Tcp->TcpSockList);
	Debug("TCP Connection Incremented: %u\n", Count(c->CurrentNumConnection));

	if (c->Session->HalfConnection)
	{
		Debug("New Half Connection: %s\n",
			direction == TCP_SERVER_TO_CLIENT ? "TCP_SERVER_TO_CLIENT" : "TCP_CLIENT_TO_SERVER"
			);
	}

	// Issue the Cancel to the session
	Cancel(c->Session->Cancel1);

	// Remove the socket from the socket list of connected
	LockList(c->ConnectingSocks);
	{
		if (Delete(c->ConnectingSocks, s))
		{
			ReleaseSock(s);
		}
	}
	UnlockList(c->ConnectingSocks);
	ReleaseSock(s);
	return true;

CLEANUP:
	// Disconnection process
	Disconnect(s);
	LockList(c->ConnectingSocks);
	{
		if (Delete(c->ConnectingSocks, s))
		{
			ReleaseSock(s);

		}
	}
	UnlockList(c->ConnectingSocks);
	ReleaseSock(s);
	return false;
}