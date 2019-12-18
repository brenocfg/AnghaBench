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
struct port_sock {int /*<<< orphan*/  input; } ;
struct inet_port {int /*<<< orphan*/  row_status; int /*<<< orphan*/  socks; } ;

/* Variables and functions */
 int /*<<< orphan*/  RowStatus_notInService ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct port_sock* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct port_sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct port_sock*) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  snmpd_input_close (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dns_deactivate(struct inet_port *port)
{
	while (!TAILQ_EMPTY(&port->socks)) {
		struct port_sock *sock = TAILQ_FIRST(&port->socks);
		TAILQ_REMOVE(&port->socks, sock, link);
		snmpd_input_close(&sock->input);
		free(sock);
	}
	port->row_status = RowStatus_notInService;
}