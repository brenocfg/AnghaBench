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
struct socket {struct sock* sk; } ;
struct TYPE_2__ {scalar_t__ s_addr; } ;
struct sockaddr_in {scalar_t__ sin_family; int /*<<< orphan*/  sin_port; TYPE_1__ sin_addr; } ;
struct sockaddr {int dummy; } ;
struct sock {int dummy; } ;
struct rds_sock {scalar_t__ rs_conn_addr; int /*<<< orphan*/  rs_conn_port; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int EAFNOSUPPORT ; 
 int EDESTADDRREQ ; 
 int EINVAL ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 scalar_t__ htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 struct rds_sock* rds_sk_to_rs (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 

__attribute__((used)) static int rds_connect(struct socket *sock, struct sockaddr *uaddr,
		       int addr_len, int flags)
{
	struct sock *sk = sock->sk;
	struct sockaddr_in *sin = (struct sockaddr_in *)uaddr;
	struct rds_sock *rs = rds_sk_to_rs(sk);
	int ret = 0;

	lock_sock(sk);

	if (addr_len != sizeof(struct sockaddr_in)) {
		ret = -EINVAL;
		goto out;
	}

	if (sin->sin_family != AF_INET) {
		ret = -EAFNOSUPPORT;
		goto out;
	}

	if (sin->sin_addr.s_addr == htonl(INADDR_ANY)) {
		ret = -EDESTADDRREQ;
		goto out;
	}

	rs->rs_conn_addr = sin->sin_addr.s_addr;
	rs->rs_conn_port = sin->sin_port;

out:
	release_sock(sk);
	return ret;
}