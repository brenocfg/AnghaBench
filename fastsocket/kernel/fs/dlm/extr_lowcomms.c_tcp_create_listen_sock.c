#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct socket {TYPE_2__* ops; TYPE_1__* sk; } ;
struct sockaddr_storage {int dummy; } ;
struct sockaddr_in6 {int dummy; } ;
struct sockaddr_in {int dummy; } ;
struct sockaddr {int dummy; } ;
struct connection {struct socket* sock; int /*<<< orphan*/  connect_action; int /*<<< orphan*/  rx_action; } ;
typedef  int /*<<< orphan*/  one ;
struct TYPE_8__ {int ci_tcp_port; } ;
struct TYPE_7__ {scalar_t__ ss_family; } ;
struct TYPE_6__ {int (* bind ) (struct socket*,struct sockaddr*,int) ;int (* listen ) (struct socket*,int) ;} ;
struct TYPE_5__ {struct connection* sk_user_data; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SOL_TCP ; 
 int /*<<< orphan*/  SO_KEEPALIVE ; 
 int /*<<< orphan*/  SO_REUSEADDR ; 
 int /*<<< orphan*/  TCP_NODELAY ; 
 TYPE_4__ dlm_config ; 
 TYPE_3__** dlm_local_addr ; 
 int kernel_setsockopt (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  log_print (char*,...) ; 
 int /*<<< orphan*/  make_sockaddr (struct sockaddr_storage*,int,int*) ; 
 int sock_create_kern (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct socket**) ; 
 int /*<<< orphan*/  sock_release (struct socket*) ; 
 int stub1 (struct socket*,struct sockaddr*,int) ; 
 int stub2 (struct socket*,int) ; 
 int /*<<< orphan*/  tcp_accept_from_sock ; 
 int /*<<< orphan*/  tcp_connect_to_sock ; 

__attribute__((used)) static struct socket *tcp_create_listen_sock(struct connection *con,
					     struct sockaddr_storage *saddr)
{
	struct socket *sock = NULL;
	int result = 0;
	int one = 1;
	int addr_len;

	if (dlm_local_addr[0]->ss_family == AF_INET)
		addr_len = sizeof(struct sockaddr_in);
	else
		addr_len = sizeof(struct sockaddr_in6);

	/* Create a socket to communicate with */
	result = sock_create_kern(dlm_local_addr[0]->ss_family, SOCK_STREAM,
				  IPPROTO_TCP, &sock);
	if (result < 0) {
		log_print("Can't create listening comms socket");
		goto create_out;
	}

	/* Turn off Nagle's algorithm */
	kernel_setsockopt(sock, SOL_TCP, TCP_NODELAY, (char *)&one,
			  sizeof(one));

	result = kernel_setsockopt(sock, SOL_SOCKET, SO_REUSEADDR,
				   (char *)&one, sizeof(one));

	if (result < 0) {
		log_print("Failed to set SO_REUSEADDR on socket: %d", result);
	}
	sock->sk->sk_user_data = con;
	con->rx_action = tcp_accept_from_sock;
	con->connect_action = tcp_connect_to_sock;
	con->sock = sock;

	/* Bind to our port */
	make_sockaddr(saddr, dlm_config.ci_tcp_port, &addr_len);
	result = sock->ops->bind(sock, (struct sockaddr *) saddr, addr_len);
	if (result < 0) {
		log_print("Can't bind to port %d", dlm_config.ci_tcp_port);
		sock_release(sock);
		sock = NULL;
		con->sock = NULL;
		goto create_out;
	}
	result = kernel_setsockopt(sock, SOL_SOCKET, SO_KEEPALIVE,
				 (char *)&one, sizeof(one));
	if (result < 0) {
		log_print("Set keepalive failed: %d", result);
	}

	result = sock->ops->listen(sock, 5);
	if (result < 0) {
		log_print("Can't listen on port %d", dlm_config.ci_tcp_port);
		sock_release(sock);
		sock = NULL;
		goto create_out;
	}

create_out:
	return sock;
}