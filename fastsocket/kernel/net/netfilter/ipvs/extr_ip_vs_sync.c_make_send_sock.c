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
struct socket {TYPE_1__* ops; int /*<<< orphan*/  sk; } ;
struct sockaddr {int dummy; } ;
struct TYPE_2__ {int (* connect ) (struct socket*,struct sockaddr*,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 struct socket* ERR_PTR (int) ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int bind_mcastif_addr (struct socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_vs_master_mcast_ifn ; 
 int /*<<< orphan*/  mcast_addr ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int set_mcast_if (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_mcast_loop (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_mcast_ttl (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_sock_size (int /*<<< orphan*/ ,int,int) ; 
 int sock_create_kern (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct socket**) ; 
 int /*<<< orphan*/  sock_release (struct socket*) ; 
 int stub1 (struct socket*,struct sockaddr*,int,int /*<<< orphan*/ ) ; 
 int sysctl_sync_sock_size () ; 

__attribute__((used)) static struct socket * make_send_sock(void)
{
	struct socket *sock;
	int result;

	/* First create a socket */
	result = sock_create_kern(PF_INET, SOCK_DGRAM, IPPROTO_UDP, &sock);
	if (result < 0) {
		pr_err("Error during creation of socket; terminating\n");
		return ERR_PTR(result);
	}

	result = set_mcast_if(sock->sk, ip_vs_master_mcast_ifn);
	if (result < 0) {
		pr_err("Error setting outbound mcast interface\n");
		goto error;
	}

	set_mcast_loop(sock->sk, 0);
	set_mcast_ttl(sock->sk, 1);
	result = sysctl_sync_sock_size();
	if (result > 0)
		set_sock_size(sock->sk, 1, result);

	result = bind_mcastif_addr(sock, ip_vs_master_mcast_ifn);
	if (result < 0) {
		pr_err("Error binding address of the mcast interface\n");
		goto error;
	}

	result = sock->ops->connect(sock, (struct sockaddr *) &mcast_addr,
			sizeof(struct sockaddr), 0);
	if (result < 0) {
		pr_err("Error connecting to the multicast addr\n");
		goto error;
	}

	return sock;

  error:
	sock_release(sock);
	return ERR_PTR(result);
}