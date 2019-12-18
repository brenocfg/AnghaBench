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
struct port_sock {int dummy; } ;
struct inet_port {int /*<<< orphan*/  row_status; int /*<<< orphan*/  socks; } ;

/* Variables and functions */
 int /*<<< orphan*/  RowStatus_active ; 
 int const SNMP_ERR_NOERROR ; 
 struct port_sock* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_NEXT (struct port_sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int ipv4_activate_sock (struct port_sock*) ; 
 int /*<<< orphan*/  link ; 

__attribute__((used)) static int
ipv4_activate(struct inet_port *p)
{
	struct port_sock *sock = TAILQ_FIRST(&p->socks);
	assert(sock);
	assert(!TAILQ_NEXT(sock, link));

	const int ret = ipv4_activate_sock(sock);
	if (ret == SNMP_ERR_NOERROR)
		p->row_status = RowStatus_active;

	return (ret);
}