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
typedef  int /*<<< orphan*/  UCHAR ;
typedef  int /*<<< orphan*/  RUDP_STACK_RPC_RECV_PROC ;
typedef  int /*<<< orphan*/  RUDP_STACK_INTERRUPTS_PROC ;
typedef  int /*<<< orphan*/  RUDP_STACK ;
typedef  int /*<<< orphan*/  IP ;

/* Variables and functions */
 scalar_t__ IsEmptyStr (char*) ; 
 int /*<<< orphan*/  ListenTcpForPopupFirewallDialog () ; 
 int /*<<< orphan*/ * NewRUDP (int,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/  volatile*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ g_no_rudp_server ; 

RUDP_STACK *NewRUDPServer(char *svc_name, RUDP_STACK_INTERRUPTS_PROC *proc_interrupts, RUDP_STACK_RPC_RECV_PROC *proc_rpc_recv, void *param, UINT port, bool no_natt_register, bool over_dns_mode, volatile UINT *natt_global_udp_port, UCHAR rand_port_id, IP *listen_ip)
{
	RUDP_STACK *r;
	// Validate arguments
	if (IsEmptyStr(svc_name))
	{
		return NULL;
	}

	if (g_no_rudp_server)
	{
		return NULL;
	}

	ListenTcpForPopupFirewallDialog();

	r = NewRUDP(true, svc_name, proc_interrupts, proc_rpc_recv, param, port, NULL, NULL, no_natt_register, over_dns_mode, NULL, natt_global_udp_port, rand_port_id, listen_ip);

	if (r == NULL)
	{
		return NULL;
	}

	return r;
}