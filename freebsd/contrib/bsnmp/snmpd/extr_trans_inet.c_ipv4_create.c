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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int sin_len; int /*<<< orphan*/  sin_port; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct port_sock {struct inet_port* port; int /*<<< orphan*/  bind_addr; int /*<<< orphan*/  input; } ;
struct inet_port_params {int addr_len; int /*<<< orphan*/  port; int /*<<< orphan*/  addr; } ;
struct inet_port {int /*<<< orphan*/  socks; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int SNMP_ERR_GENERR ; 
 int SNMP_ERR_INCONS_VALUE ; 
 int SNMP_ERR_NOERROR ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct port_sock*,int /*<<< orphan*/ ) ; 
 struct port_sock* calloc (int,int) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snmpd_input_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ipv4_create(struct inet_port *port, struct inet_port_params *params)
{
	uint32_t ip;

	if (params->addr_len != 4)
		return (SNMP_ERR_INCONS_VALUE);

	memcpy(&ip, params->addr, 4);
	struct port_sock *sock = calloc(1, sizeof(struct port_sock));
	if (sock == NULL)
		return (SNMP_ERR_GENERR);

	snmpd_input_init(&sock->input);

	TAILQ_INSERT_HEAD(&port->socks, sock, link);

	struct sockaddr_in *sin =
	    (struct sockaddr_in *)&sock->bind_addr;

	sin->sin_len = sizeof(struct sockaddr_in);
	sin->sin_family = AF_INET;
	sin->sin_addr.s_addr = htonl(ip);
	sin->sin_port = htons(params->port);

	sock->port = port;

	return (SNMP_ERR_NOERROR);
}