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
struct socket {int /*<<< orphan*/  sk; } ;
struct TYPE_2__ {scalar_t__ s_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_family; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_zero; } ;
struct sockaddr {int dummy; } ;
struct rds_sock {scalar_t__ rs_bound_addr; int /*<<< orphan*/  rs_bound_port; scalar_t__ rs_conn_addr; int /*<<< orphan*/  rs_conn_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int ENOTCONN ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct rds_sock* rds_sk_to_rs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rds_getname(struct socket *sock, struct sockaddr *uaddr,
		       int *uaddr_len, int peer)
{
	struct sockaddr_in *sin = (struct sockaddr_in *)uaddr;
	struct rds_sock *rs = rds_sk_to_rs(sock->sk);

	memset(sin->sin_zero, 0, sizeof(sin->sin_zero));

	/* racey, don't care */
	if (peer) {
		if (!rs->rs_conn_addr)
			return -ENOTCONN;

		sin->sin_port = rs->rs_conn_port;
		sin->sin_addr.s_addr = rs->rs_conn_addr;
	} else {
		sin->sin_port = rs->rs_bound_port;
		sin->sin_addr.s_addr = rs->rs_bound_addr;
	}

	sin->sin_family = AF_INET;

	*uaddr_len = sizeof(*sin);
	return 0;
}