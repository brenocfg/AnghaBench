#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  SOCK ;
typedef  int /*<<< orphan*/  IP ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/ * ConnectEx4 (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * VPN_RUDP_SVC_NAME ; 
 int /*<<< orphan*/ * WinConnectEx3 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

SOCK *TcpConnectEx3(char *hostname, UINT port, UINT timeout, bool *cancel_flag, void *hWnd, bool no_nat_t, UINT *nat_t_error_code, bool try_start_ssl, IP *ret_ip)
{
#ifdef	OS_WIN32
	if (hWnd == NULL)
	{
#endif	// OS_WIN32
		return ConnectEx4(hostname, port, timeout, cancel_flag, (no_nat_t ? NULL : VPN_RUDP_SVC_NAME), nat_t_error_code, try_start_ssl, true, ret_ip);
#ifdef	OS_WIN32
	}
	else
	{
		return WinConnectEx3((HWND)hWnd, hostname, port, timeout, 0, NULL, NULL, nat_t_error_code, (no_nat_t ? NULL : VPN_RUDP_SVC_NAME), try_start_ssl);
	}
#endif	// OS_WIN32
}