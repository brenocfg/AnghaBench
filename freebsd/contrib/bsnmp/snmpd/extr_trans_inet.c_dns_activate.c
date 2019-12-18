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
struct sockaddr_in6 {int dummy; } ;
struct sockaddr_in {int dummy; } ;
struct port_sock {int /*<<< orphan*/  bind_addr; struct inet_port* port; int /*<<< orphan*/  input; } ;
struct inet_port {char* dns_addr; int /*<<< orphan*/  row_status; int /*<<< orphan*/  socks; int /*<<< orphan*/  dns_port; } ;
struct addrinfo {scalar_t__ ai_family; int ai_flags; scalar_t__ ai_addr; struct addrinfo* ai_next; int /*<<< orphan*/  ai_socktype; } ;
typedef  int /*<<< orphan*/  hints ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 scalar_t__ AF_UNSPEC ; 
 int AI_ADDRCONFIG ; 
 int AI_NUMERICSERV ; 
 int AI_PASSIVE ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  RowStatus_active ; 
 int SNMP_ERR_GENERR ; 
 int SNMP_ERR_NOERROR ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct port_sock*,int /*<<< orphan*/ ) ; 
 struct port_sock* calloc (int,int) ; 
 int /*<<< orphan*/  free (struct port_sock*) ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int /*<<< orphan*/  gai_strerror (int) ; 
 int getaddrinfo (char*,char*,struct addrinfo*,struct addrinfo**) ; 
 int ipv4_activate_sock (struct port_sock*) ; 
 int ipv6_activate_sock (struct port_sock*) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snmpd_input_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dns_activate(struct inet_port *port)
{
	struct addrinfo hints;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;		// XXX udp-only
	hints.ai_flags = AI_ADDRCONFIG | AI_PASSIVE | AI_NUMERICSERV;

	char portbuf[8];
	sprintf(portbuf, "%hu", ntohs(port->dns_port));

	struct addrinfo *res0;
	int error = getaddrinfo(port->dns_addr[0] == '\0'
	    ? NULL : port->dns_addr,
	    portbuf, &hints, &res0);

	if (error) {
		syslog(LOG_ERR, "cannot resolve address '%s': %s",
		    port->dns_addr, gai_strerror(error));
		return (SNMP_ERR_GENERR);
	}

	for (struct addrinfo *res = res0; res != NULL; res = res->ai_next) {
		if (res->ai_family != AF_INET && res->ai_family != AF_INET6)
			continue;

		struct port_sock *sock = calloc(1, sizeof(struct port_sock));
		if (sock == NULL)
			return (SNMP_ERR_GENERR);

		snmpd_input_init(&sock->input);
		sock->port = port;

		int ret = SNMP_ERR_NOERROR;

		if (res->ai_family == AF_INET) {
			*(struct sockaddr_in *)&sock->bind_addr =
			    *(struct sockaddr_in *)(void *)res->ai_addr;
			ret = ipv4_activate_sock(sock);
		} else {
			*(struct sockaddr_in6 *)&sock->bind_addr =
			    *(struct sockaddr_in6 *)(void *)res->ai_addr;
			ret = ipv6_activate_sock(sock);
		}

		if (ret != SNMP_ERR_NOERROR)
			free(sock);
		else
			TAILQ_INSERT_HEAD(&port->socks, sock, link);
	}

	if (!TAILQ_EMPTY(&port->socks))
		port->row_status = RowStatus_active;

	freeaddrinfo(res0);
	return (SNMP_ERR_GENERR);
}