#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {TYPE_1__* Session; int /*<<< orphan*/  ServerX; int /*<<< orphan*/  ConnectingSocks; int /*<<< orphan*/  ServerName; } ;
struct TYPE_15__ {int /*<<< orphan*/  RemoteX; int /*<<< orphan*/  ref; } ;
struct TYPE_14__ {int SessionTimeOuted; scalar_t__ Halt; } ;
typedef  TYPE_2__ SOCK ;
typedef  TYPE_3__ CONNECTION ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CONNECTING_TIMEOUT ; 
 TYPE_2__* ClientConnectGetSocket (TYPE_3__*,int) ; 
 int CompareX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ Delete (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  Disconnect (TYPE_2__*) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSock (TYPE_2__*) ; 
 int /*<<< orphan*/  SetTimeout (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int StartSSLEx (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 

SOCK *ClientAdditionalConnectToServer(CONNECTION *c)
{
	SOCK *s;
	// Validate arguments
	if (c == NULL)
	{
		return NULL;
	}

	// Socket connection
	s = ClientConnectGetSocket(c, true);
	if (s == NULL)
	{
		// Connection failure
		return NULL;
	}

	// Add the socket to the list
	LockList(c->ConnectingSocks);
	{
		Add(c->ConnectingSocks, s);
		AddRef(s->ref);
	}
	UnlockList(c->ConnectingSocks);

	if (c->Session->Halt)
	{
		// Stop
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
		return NULL;
	}

	// Time-out
	SetTimeout(s, CONNECTING_TIMEOUT);

	// Start the SSL communication
	if (StartSSLEx(s, NULL, NULL, 0, c->ServerName) == false)
	{
		// SSL communication failure
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
		return NULL;
	}

	// Check the certificate
	if (CompareX(s->RemoteX, c->ServerX) == false)
	{
		// The certificate is invalid
		Disconnect(s);
		c->Session->SessionTimeOuted = true;
	}

	return s;
}