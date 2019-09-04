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

/* Variables and functions */
 int /*<<< orphan*/ * ConnectEx4 (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,char*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 

SOCK *ConnectEx3(char *hostname, UINT port, UINT timeout, bool *cancel_flag, char *nat_t_svc_name, UINT *nat_t_error_code, bool try_start_ssl, bool no_get_hostname)
{
	return ConnectEx4(hostname, port, timeout, cancel_flag, nat_t_svc_name, nat_t_error_code, try_start_ssl, no_get_hostname, NULL);
}