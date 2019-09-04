#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X ;
typedef  scalar_t__ UINT64 ;
struct TYPE_17__ {int Expired; int Ok; int /*<<< orphan*/ * ServerX; scalar_t__ UserSelected; TYPE_3__* Connection; int /*<<< orphan*/ * CheckCertProc; } ;
struct TYPE_16__ {int /*<<< orphan*/ * CheckCertProc; } ;
struct TYPE_15__ {TYPE_11__* Session; TYPE_1__* FirstSock; int /*<<< orphan*/ * ServerX; scalar_t__ UseTicket; int /*<<< orphan*/ * Cedar; } ;
struct TYPE_14__ {int CheckServerCert; int /*<<< orphan*/  lock; int /*<<< orphan*/ * ServerCert; } ;
struct TYPE_13__ {int /*<<< orphan*/ * RemoteX; } ;
struct TYPE_12__ {int LinkModeClient; TYPE_2__* Link; TYPE_4__* ClientAuth; } ;
typedef  int /*<<< orphan*/  THREAD ;
typedef  TYPE_3__ CONNECTION ;
typedef  TYPE_4__ CLIENT_AUTH ;
typedef  TYPE_5__ CHECK_CERT_THREAD_PROC ;
typedef  int /*<<< orphan*/  CEDAR ;

/* Variables and functions */
 scalar_t__ CONNECTING_POOLING_SPAN ; 
 scalar_t__ CheckSignatureByCa (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ CheckSignatureByCaLinkMode (TYPE_11__*,int /*<<< orphan*/ *) ; 
 scalar_t__ CheckXDateNow (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ClientCheckServerCertThread ; 
 int /*<<< orphan*/  ClientUploadNoop (TYPE_3__*) ; 
 int /*<<< orphan*/ * CloneX (int /*<<< orphan*/ *) ; 
 int CompareX (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Free (TYPE_5__*) ; 
 int /*<<< orphan*/  FreeX (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NewThread (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  ReleaseThread (int /*<<< orphan*/ *) ; 
 scalar_t__ Tick64 () ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WaitThread (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  WaitThreadInit (int /*<<< orphan*/ *) ; 
 TYPE_5__* ZeroMalloc (int) ; 

bool ClientCheckServerCert(CONNECTION *c, bool *expired)
{
	CLIENT_AUTH *auth;
	X *x;
	CHECK_CERT_THREAD_PROC *p;
	THREAD *thread;
	CEDAR *cedar;
	bool ret;
	UINT64 start;
	// Validate arguments
	if (c == NULL)
	{
		return false;
	}

	if (expired != NULL)
	{
		*expired = false;
	}

	auth = c->Session->ClientAuth;
	cedar = c->Cedar;

	if (auth->CheckCertProc == NULL && c->Session->LinkModeClient == false)
	{
		// No checking function
		return true;
	}

	if (c->Session->LinkModeClient && c->Session->Link->CheckServerCert == false)
	{
		// It's in cascade connection mode, but do not check the server certificate
		return true;
	}

	if (c->UseTicket)
	{
		// Check the certificate of the redirected VPN server
		if (CompareX(c->FirstSock->RemoteX, c->ServerX) == false)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	x = CloneX(c->FirstSock->RemoteX);
	if (x == NULL)
	{
		// Strange error occurs
		return false;
	}

	if (CheckXDateNow(x))
	{
		// Check whether it is signed by the root certificate to trust
		if (c->Session->LinkModeClient == false)
		{
			// Normal VPN Client mode
			if (CheckSignatureByCa(cedar, x))
			{
				// This certificate can be trusted because it is signed
				FreeX(x);
				return true;
			}
		}
		else
		{
			// Cascade connection mode
			if (CheckSignatureByCaLinkMode(c->Session, x))
			{
				// This certificate can be trusted because it is signed
				FreeX(x);
				return true;
			}
		}
	}

	if (c->Session->LinkModeClient)
	{
		if (CheckXDateNow(x))
		{
			Lock(c->Session->Link->lock);
			{
				if (c->Session->Link->ServerCert != NULL)
				{
					if (CompareX(c->Session->Link->ServerCert, x))
					{
						Unlock(c->Session->Link->lock);
						// Exactly match the certificate that is registered in the cascade configuration
						FreeX(x);
						return true;
					}
				}
			}
			Unlock(c->Session->Link->lock);
		}
		else
		{
			if (expired != NULL)
			{
				*expired = true;
			}
		}

		// Verification failure at this point in the case of cascade connection mode
		FreeX(x);
		return false;
	}

	p = ZeroMalloc(sizeof(CHECK_CERT_THREAD_PROC));
	p->ServerX = x;
	p->CheckCertProc = auth->CheckCertProc;
	p->Connection = c;

	// Create a thread
	thread = NewThread(ClientCheckServerCertThread, p);
	WaitThreadInit(thread);

	// Poll at 0.5-second intervals until the user selects whether the connection
	start = Tick64();
	while (true)
	{
		if ((Tick64() - start) > CONNECTING_POOLING_SPAN)
		{
			// Send a NOOP periodically for disconnection prevention
			start = Tick64();
			ClientUploadNoop(c);
		}
		if (p->UserSelected)
		{
			// User-selected
			break;
		}
		WaitThread(thread, 500);
	}

	if (expired != NULL)
	{
		*expired = p->Expired;
	}

	ret = p->Ok;
	FreeX(p->ServerX);
	Free(p);
	ReleaseThread(thread);

	return ret;
}