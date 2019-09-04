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
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  SOCK ;
typedef  int /*<<< orphan*/  IP ;

/* Variables and functions */
 int /*<<< orphan*/ * TcpConnectEx3 (char*,scalar_t__,int /*<<< orphan*/ ,int*,void*,int,scalar_t__*,int,int /*<<< orphan*/ *) ; 

SOCK *TcpIpConnectEx(char *hostname, UINT port, bool *cancel_flag, void *hWnd, UINT *nat_t_error_code, bool no_nat_t, bool try_start_ssl, IP *ret_ip)
{
	SOCK *s = NULL;
	UINT dummy_int = 0;
	// Validate arguments
	if (nat_t_error_code == NULL)
	{
		nat_t_error_code = &dummy_int;
	}
	*nat_t_error_code = 0;
	if (hostname == NULL || port == 0)
	{
		return NULL;
	}

	s = TcpConnectEx3(hostname, port, 0, cancel_flag, hWnd, no_nat_t, nat_t_error_code, try_start_ssl, ret_ip);
	if (s == NULL)
	{
		return NULL;
	}

	return s;
}