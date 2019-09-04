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
struct TYPE_4__ {int TargetIpAndPortInited; int DoNotSetTargetConnectedSock; int /*<<< orphan*/  Lock; int /*<<< orphan*/ * TargetConnectedSock; int /*<<< orphan*/  TargetConnectedEvent; int /*<<< orphan*/  SockEvent; scalar_t__ TargetPort; int /*<<< orphan*/  TargetIp; } ;
typedef  int /*<<< orphan*/  SOCK_EVENT ;
typedef  int /*<<< orphan*/  SOCK ;
typedef  TYPE_1__ RUDP_STACK ;
typedef  int /*<<< orphan*/  IP ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Disconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeRUDP (TYPE_1__*) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 TYPE_1__* NewRUDP (int,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RUDP_ERROR_OK ; 
 scalar_t__ RUDP_ERROR_TIMEOUT ; 
 scalar_t__ RUDP_ERROR_UNKNOWN ; 
 scalar_t__ RUDP_ERROR_USER_CANCELED ; 
 scalar_t__ RUDP_TIMEOUT ; 
 int /*<<< orphan*/  ReleaseSock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetSockEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WaitEx (int /*<<< orphan*/ ,scalar_t__,int*) ; 

SOCK *NewRUDPClientDirect(char *svc_name, IP *ip, UINT port, UINT *error_code, UINT timeout, bool *cancel, SOCK *sock, SOCK_EVENT *sock_event, UINT local_port, bool over_dns_mode)
{
	RUDP_STACK *r;
	UINT dummy_int = 0;
	SOCK *ret = NULL;
	// Validate arguments
	if (error_code == NULL)
	{
		error_code = &dummy_int;
	}
	if (timeout == 0)
	{
		timeout = RUDP_TIMEOUT;
	}
	*error_code = RUDP_ERROR_UNKNOWN;
	if (svc_name == NULL || ip == NULL || port == 0)
	{
		return NULL;
	}

	r = NewRUDP(false, svc_name, NULL, NULL, NULL, local_port, sock, sock_event, false, over_dns_mode, ip, NULL, 0, NULL);
	if (r == NULL)
	{
		*error_code = RUDP_ERROR_UNKNOWN;
		return NULL;
	}

	// Set the port number and the target IP address
	Lock(r->Lock);
	{
		Copy(&r->TargetIp, ip, sizeof(IP));
		r->TargetPort = port;
		r->TargetIpAndPortInited = true;
	}
	Unlock(r->Lock);
	SetSockEvent(r->SockEvent);

	// Wait for a connection success/failure to the target IP address
	WaitEx(r->TargetConnectedEvent, timeout, cancel);
	Lock(r->Lock);
	{
		if (r->TargetConnectedSock != NULL)
		{
			// The connection succeeded
			ret = r->TargetConnectedSock;
			r->TargetConnectedSock = NULL;
		}
		else
		{
			r->DoNotSetTargetConnectedSock = true;
		}
	}
	Unlock(r->Lock);

	if (ret == NULL)
	{
		// Stop the R-UDP stack if the connection has failed
		*error_code = RUDP_ERROR_TIMEOUT;
		FreeRUDP(r);
	}
	else if (cancel != NULL && (*cancel))
	{
		// User canceled
		*error_code = RUDP_ERROR_USER_CANCELED;

		Disconnect(ret);
		ReleaseSock(ret);

		ret = NULL;
	}
	else
	{
		*error_code = RUDP_ERROR_OK;
	}

	return ret;
}