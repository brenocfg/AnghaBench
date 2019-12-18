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
typedef  int /*<<< orphan*/  RUDP_STACK_RPC_RECV_PROC ;
typedef  int /*<<< orphan*/  RUDP_STACK_INTERRUPTS_PROC ;

/* Variables and functions */
 int /*<<< orphan*/ * ListenRUDPEx (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

SOCK *ListenRUDP(char *svc_name, RUDP_STACK_INTERRUPTS_PROC *proc_interrupts, RUDP_STACK_RPC_RECV_PROC *proc_rpc_recv, void *param, UINT port, bool no_natt_register, bool over_dns_mode)
{
	return ListenRUDPEx(svc_name, proc_interrupts, proc_rpc_recv, param, port, no_natt_register, over_dns_mode, NULL, 0, NULL);
}