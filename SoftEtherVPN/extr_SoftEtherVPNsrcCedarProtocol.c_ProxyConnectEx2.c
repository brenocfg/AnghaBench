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
typedef  int /*<<< orphan*/  wpc_connect ;
struct TYPE_4__ {int /*<<< orphan*/  ProxyPassword; int /*<<< orphan*/  ProxyUsername; void* Port; int /*<<< orphan*/  HostName; void* ProxyPort; int /*<<< orphan*/  ProxyHostName; } ;
typedef  TYPE_1__ WPC_CONNECT ;
typedef  void* UINT ;
typedef  int /*<<< orphan*/  SOCK ;
typedef  int /*<<< orphan*/  CONNECTION ;

/* Variables and functions */
 int /*<<< orphan*/ * ProxyConnectEx3 (int /*<<< orphan*/ *,TYPE_1__*,int,int*,void*,void*) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

SOCK *ProxyConnectEx2(CONNECTION *c, char *proxy_host_name, UINT proxy_port,
				   char *server_host_name, UINT server_port,
				   char *username, char *password, bool additional_connect,
				   bool *cancel_flag, void *hWnd, UINT timeout)
{
	WPC_CONNECT wpc_connect;
	Zero(&wpc_connect, sizeof(wpc_connect));

	StrCpy(wpc_connect.ProxyHostName, sizeof(wpc_connect.ProxyHostName), proxy_host_name);
	wpc_connect.ProxyPort = proxy_port;
	StrCpy(wpc_connect.HostName, sizeof(wpc_connect.HostName), server_host_name);
	wpc_connect.Port = server_port;
	StrCpy(wpc_connect.ProxyUsername, sizeof(wpc_connect.ProxyUsername), username);
	StrCpy(wpc_connect.ProxyPassword, sizeof(wpc_connect.ProxyPassword), password);

	return ProxyConnectEx3(c, &wpc_connect, additional_connect, cancel_flag, hWnd, timeout);
}