#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  c ;
struct TYPE_10__ {int ProxyType; int /*<<< orphan*/  ProxyUsername; int /*<<< orphan*/  Port; int /*<<< orphan*/  HostName; int /*<<< orphan*/  ProxyPort; int /*<<< orphan*/  ProxyHostName; } ;
typedef  TYPE_1__ WPC_CONNECT ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_11__ {int /*<<< orphan*/  Err; } ;
typedef  int /*<<< orphan*/  SOCK ;
typedef  TYPE_2__ CONNECTION ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_CONNECT_FAILED ; 
 int /*<<< orphan*/  ERR_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERR_NO_ERROR ; 
#define  PROXY_DIRECT 131 
#define  PROXY_HTTP 130 
#define  PROXY_SOCKS 129 
#define  PROXY_SOCKS5 128 
 int /*<<< orphan*/ * ProxyConnectEx3 (TYPE_2__*,TYPE_1__*,int,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * Socks5Connect (TYPE_2__*,TYPE_1__*,int,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SocksConnectEx2 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TcpConnectEx3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 

SOCK *WpcSockConnectEx(WPC_CONNECT *param, UINT *error_code, UINT timeout, bool *cancel)
{
	CONNECTION c;
	SOCK *sock;
	UINT err = ERR_NO_ERROR;
	// Validate arguments
	if (param == NULL)
	{
		return NULL;
	}

	Zero(&c, sizeof(c));

	sock = NULL;
	err = ERR_INTERNAL_ERROR;

	switch (param->ProxyType)
	{
	case PROXY_DIRECT:
		sock = TcpConnectEx3(param->HostName, param->Port, timeout, cancel, NULL, true, NULL, false, NULL);
		if (sock == NULL)
		{
			err = ERR_CONNECT_FAILED;
		}
		break;

	case PROXY_HTTP:
		sock = ProxyConnectEx3(&c, param, false, cancel, NULL, timeout);
		if (sock == NULL)
		{
			err = c.Err;
		}
		break;

	case PROXY_SOCKS:
		// SOCKS4 connection
		sock = SocksConnectEx2(&c, param->ProxyHostName, param->ProxyPort,
			param->HostName, param->Port,
			param->ProxyUsername, false, cancel, NULL, timeout, NULL);
		if (sock == NULL)
		{
			err = c.Err;
		}
		break;

	case PROXY_SOCKS5:
		// SOCKS5 connection
		sock = Socks5Connect(&c, param, false, cancel, NULL, timeout, NULL);
		if (sock == NULL)
		{
			err = c.Err;
		}
	}

	if (error_code != NULL)
	{
		*error_code = err;
	}

	return sock;
}