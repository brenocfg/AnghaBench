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
typedef  scalar_t__ UINT ;
struct TYPE_5__ {int /*<<< orphan*/ * FirstSock; void* Err; scalar_t__ Halt; } ;
typedef  int /*<<< orphan*/  SOCK ;
typedef  int /*<<< orphan*/  IP ;
typedef  TYPE_1__ CONNECTION ;

/* Variables and functions */
 int /*<<< orphan*/  CONNECTING_TIMEOUT_PROXY ; 
 int /*<<< orphan*/  Disconnect (int /*<<< orphan*/ *) ; 
 void* ERR_CONNECT_FAILED ; 
 void* ERR_PROXY_CONNECT_FAILED ; 
 void* ERR_USER_CANCEL ; 
 int GetIP (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ INFINITE ; 
 scalar_t__ MIN (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ReleaseSock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetTimeout (int /*<<< orphan*/ *,scalar_t__) ; 
 int SocksRecvResponsePacket (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int SocksSendRequestPacket (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * TcpConnectEx3 (char*,scalar_t__,scalar_t__,int*,void*,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

SOCK *SocksConnectEx2(CONNECTION *c, char *proxy_host_name, UINT proxy_port,
				   char *server_host_name, UINT server_port,
				   char *username, bool additional_connect,
				   bool *cancel_flag, void *hWnd, UINT timeout, IP *ret_ip)
{
	SOCK *s = NULL;
	IP ip;
	// Validate arguments
	if (c == NULL || proxy_host_name == NULL || proxy_port == 0 || server_host_name == NULL
		|| server_port == 0)
	{
		if (c != NULL)
		{
			c->Err = ERR_PROXY_CONNECT_FAILED;
		}
		return NULL;
	}

	// Get the IP address of the destination server
	if (GetIP(&ip, server_host_name) == false)
	{
		// Failure
		c->Err = ERR_CONNECT_FAILED;
		return NULL;
	}

	if (c->Halt)
	{
		// Stop
		c->Err = ERR_USER_CANCEL;
		return NULL;
	}

	// Connection
	s = TcpConnectEx3(proxy_host_name, proxy_port, timeout, cancel_flag, hWnd, true, NULL, false, ret_ip);
	if (s == NULL)
	{
		// Failure
		c->Err = ERR_PROXY_CONNECT_FAILED;
		return NULL;
	}

	// Timeout setting
	SetTimeout(s, MIN(CONNECTING_TIMEOUT_PROXY, (timeout == 0 ? INFINITE : timeout)));

	if (additional_connect == false)
	{
		c->FirstSock = s;
	}

	// Request packet transmission
	if (SocksSendRequestPacket(c, s, server_port, &ip, username) == false)
	{
		// Failure
		if (additional_connect == false)
		{
			c->FirstSock = NULL;
		}
		Disconnect(s);
		ReleaseSock(s);
		return NULL;
	}

	// Receive a response packet
	if (SocksRecvResponsePacket(c, s) == false)
	{
		// Failure
		if (additional_connect == false)
		{
			c->FirstSock = NULL;
		}
		Disconnect(s);
		ReleaseSock(s);
		return NULL;
	}

	SetTimeout(s, INFINITE);

	return s;
}