#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_9__ {TYPE_1__* UdpSock; } ;
struct TYPE_8__ {int ListenMode; int Connected; TYPE_3__* R_UDP_Stack; int /*<<< orphan*/  LocalPort; int /*<<< orphan*/  Type; } ;
struct TYPE_7__ {int /*<<< orphan*/  LocalPort; } ;
typedef  TYPE_2__ SOCK ;
typedef  int /*<<< orphan*/  RUDP_STACK_RPC_RECV_PROC ;
typedef  int /*<<< orphan*/  RUDP_STACK_INTERRUPTS_PROC ;
typedef  TYPE_3__ RUDP_STACK ;
typedef  int /*<<< orphan*/  IP ;

/* Variables and functions */
 TYPE_3__* NewRUDPServer (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/  volatile*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* NewSock () ; 
 int /*<<< orphan*/  SOCK_RUDP_LISTEN ; 

SOCK *ListenRUDPEx(char *svc_name, RUDP_STACK_INTERRUPTS_PROC *proc_interrupts, RUDP_STACK_RPC_RECV_PROC *proc_rpc_recv, void *param, UINT port, bool no_natt_register, bool over_dns_mode,
				   volatile UINT *natt_global_udp_port, UCHAR rand_port_id, IP *listen_ip)
{
	SOCK *s;
	RUDP_STACK *r;

	// Creating a R-UDP stack
	r = NewRUDPServer(svc_name, proc_interrupts, proc_rpc_recv, param, port, no_natt_register, over_dns_mode, natt_global_udp_port, rand_port_id, listen_ip);
	if (r == NULL)
	{
		return NULL;
	}

	s = NewSock();

	s->Type = SOCK_RUDP_LISTEN;
	s->ListenMode = true;
	s->Connected = true;

	s->LocalPort = r->UdpSock->LocalPort;

	s->R_UDP_Stack = r;

	return s;
}