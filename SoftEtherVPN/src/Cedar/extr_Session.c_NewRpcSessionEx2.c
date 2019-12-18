#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_18__ {int /*<<< orphan*/  Build; int /*<<< orphan*/  Version; } ;
struct TYPE_17__ {int /*<<< orphan*/  UseCompress; int /*<<< orphan*/  UseEncrypt; int /*<<< orphan*/  MaxConnection; } ;
struct TYPE_16__ {int /*<<< orphan*/  Err; void* hWndForUI; } ;
struct TYPE_15__ {int ServerMode; TYPE_2__* Connection; int /*<<< orphan*/  UseCompress; int /*<<< orphan*/  UseEncrypt; int /*<<< orphan*/  MaxConnection; int /*<<< orphan*/  ClientOption; int /*<<< orphan*/  Cancel1; void* TrafficLock; int /*<<< orphan*/  HaltEvent; int /*<<< orphan*/  Traffic; int /*<<< orphan*/  LastCommTime; int /*<<< orphan*/  CreatedTime; int /*<<< orphan*/  Name; TYPE_4__* Cedar; int /*<<< orphan*/  ref; void* lock; int /*<<< orphan*/  LoggingRecordCount; } ;
typedef  int /*<<< orphan*/  SOCK ;
typedef  TYPE_1__ SESSION ;
typedef  TYPE_2__ CONNECTION ;
typedef  TYPE_3__ CLIENT_OPTION ;
typedef  TYPE_4__ CEDAR ;

/* Variables and functions */
 int /*<<< orphan*/ * ClientConnectToServer (TYPE_2__*) ; 
 int ClientDownloadHello (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int ClientUploadSignature (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 int /*<<< orphan*/  CopyStr (char*) ; 
 int /*<<< orphan*/  Malloc (int) ; 
 int /*<<< orphan*/  NewCancel () ; 
 TYPE_2__* NewClientConnectionEx (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NewCounter () ; 
 int /*<<< orphan*/  NewEvent () ; 
 void* NewLock () ; 
 int /*<<< orphan*/  NewRef () ; 
 int /*<<< orphan*/  NewTraffic () ; 
 int /*<<< orphan*/  ReleaseSession (TYPE_1__*) ; 
 int /*<<< orphan*/  Tick64 () ; 
 TYPE_1__* ZeroMalloc (int) ; 

SESSION *NewRpcSessionEx2(CEDAR *cedar, CLIENT_OPTION *option, UINT *err, char *client_str, void *hWnd)
{
	SESSION *s;
	CONNECTION *c;
	SOCK *sock;
	// Validate arguments
	if (cedar == NULL || option == NULL)
	{
		return NULL;
	}

	s = ZeroMalloc(sizeof(SESSION));

	s->LoggingRecordCount = NewCounter();
	s->lock = NewLock();
	s->ref = NewRef();
	s->Cedar = cedar;
	s->ServerMode = false;
	s->Name = CopyStr("CLIENT_RPC_SESSION");
	s->CreatedTime = s->LastCommTime = Tick64();
	s->Traffic = NewTraffic();
	s->HaltEvent = NewEvent();
	s->TrafficLock = NewLock();
	s->Cancel1 = NewCancel();

	// Copy the client connection options
	s->ClientOption = Malloc(sizeof(CLIENT_OPTION));
	Copy(s->ClientOption, option, sizeof(CLIENT_OPTION));

	s->MaxConnection = option->MaxConnection;
	s->UseEncrypt = option->UseEncrypt;
	s->UseCompress = option->UseCompress;

	// Create a connection
	c = s->Connection = NewClientConnectionEx(s, client_str, cedar->Version, cedar->Build);
	c->hWndForUI = hWnd;

	// Connect to the server
	sock = ClientConnectToServer(c);
	if (sock == NULL)
	{
		// Connection failure
		if (err != NULL)
		{
			*err = c->Err;
		}
		ReleaseSession(s);
		return NULL;
	}

	// Send a signature
	if (ClientUploadSignature(sock) == false)
	{
		// Failure
		if (err != NULL)
		{
			*err = c->Err;
		}
		ReleaseSession(s);
		return NULL;
	}

	// Receive a Hello packet
	if (ClientDownloadHello(c, sock) == false)
	{
		// Failure
		if (err != NULL)
		{
			*err = c->Err;
		}
		ReleaseSession(s);
		return NULL;
	}

	return s;
}