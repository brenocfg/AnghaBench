#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tcp_pcb {int dummy; } ;
struct TYPE_2__ {struct tcp_pcb* tcp; } ;
struct netconn {TYPE_1__ pcb; } ;

/* Variables and functions */
 int /*<<< orphan*/  err_tcp ; 
 int /*<<< orphan*/  poll_tcp ; 
 int /*<<< orphan*/  recv_tcp ; 
 int /*<<< orphan*/  sent_tcp ; 
 int /*<<< orphan*/  tcp_arg (struct tcp_pcb*,struct netconn*) ; 
 int /*<<< orphan*/  tcp_err (struct tcp_pcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_poll (struct tcp_pcb*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tcp_recv (struct tcp_pcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_sent (struct tcp_pcb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void setuptcp(struct netconn *conn)
{
	struct tcp_pcb *pcb = conn->pcb.tcp;

	tcp_arg(pcb,conn);
	tcp_recv(pcb,recv_tcp);
	tcp_sent(pcb,sent_tcp);
	tcp_poll(pcb,poll_tcp,4);
	tcp_err(pcb,err_tcp);
}