#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct socket {scalar_t__ state; } ;
struct sockaddr_dn {scalar_t__ sdn_family; int sdn_flags; } ;
struct sock {TYPE_2__* sk_dst_cache; int /*<<< orphan*/  sk_route_caps; int /*<<< orphan*/  sk_bound_dev_if; struct socket* sk_socket; } ;
struct flowi {int /*<<< orphan*/  proto; void* fld_src; void* fld_dst; int /*<<< orphan*/  oif; } ;
struct dn_scp {scalar_t__ state; int /*<<< orphan*/  segsize_loc; int /*<<< orphan*/  addr; int /*<<< orphan*/  peer; } ;
typedef  int /*<<< orphan*/  fl ;
struct TYPE_5__ {TYPE_1__* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  features; } ;

/* Variables and functions */
 scalar_t__ AF_DECnet ; 
 int /*<<< orphan*/  DNPROTO_NSP ; 
 scalar_t__ DN_CC ; 
 scalar_t__ DN_CI ; 
 scalar_t__ DN_O ; 
 scalar_t__ DN_RUN ; 
 struct dn_scp* DN_SK (struct sock*) ; 
 int ECONNREFUSED ; 
 int EHOSTUNREACH ; 
 int EINPROGRESS ; 
 int EINVAL ; 
 int EISCONN ; 
 int /*<<< orphan*/  NSP_CI ; 
 int /*<<< orphan*/  RTAX_ADVMSS ; 
 int SDF_WILD ; 
 int /*<<< orphan*/  SOCK_ZAPPED ; 
 scalar_t__ SS_CONNECTED ; 
 scalar_t__ SS_CONNECTING ; 
 scalar_t__ SS_UNCONNECTED ; 
 int dn_auto_bind (struct socket*) ; 
 int /*<<< orphan*/  dn_nsp_send_conninit (struct sock*,int /*<<< orphan*/ ) ; 
 scalar_t__ dn_route_output_sock (TYPE_2__**,struct flowi*,struct sock*,int) ; 
 void* dn_saddr2dn (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dn_sk_ports_copy (struct flowi*,struct dn_scp*) ; 
 int dn_wait_run (struct sock*,long*) ; 
 int /*<<< orphan*/  dst_metric (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct sockaddr_dn*,int) ; 
 int /*<<< orphan*/  memset (struct flowi*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sock_flag (struct sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __dn_connect(struct sock *sk, struct sockaddr_dn *addr, int addrlen, long *timeo, int flags)
{
	struct socket *sock = sk->sk_socket;
	struct dn_scp *scp = DN_SK(sk);
	int err = -EISCONN;
	struct flowi fl;

	if (sock->state == SS_CONNECTED)
		goto out;

	if (sock->state == SS_CONNECTING) {
		err = 0;
		if (scp->state == DN_RUN) {
			sock->state = SS_CONNECTED;
			goto out;
		}
		err = -ECONNREFUSED;
		if (scp->state != DN_CI && scp->state != DN_CC) {
			sock->state = SS_UNCONNECTED;
			goto out;
		}
		return dn_wait_run(sk, timeo);
	}

	err = -EINVAL;
	if (scp->state != DN_O)
		goto out;

	if (addr == NULL || addrlen != sizeof(struct sockaddr_dn))
		goto out;
	if (addr->sdn_family != AF_DECnet)
		goto out;
	if (addr->sdn_flags & SDF_WILD)
		goto out;

	if (sock_flag(sk, SOCK_ZAPPED)) {
		err = dn_auto_bind(sk->sk_socket);
		if (err)
			goto out;
	}

	memcpy(&scp->peer, addr, sizeof(struct sockaddr_dn));

	err = -EHOSTUNREACH;
	memset(&fl, 0, sizeof(fl));
	fl.oif = sk->sk_bound_dev_if;
	fl.fld_dst = dn_saddr2dn(&scp->peer);
	fl.fld_src = dn_saddr2dn(&scp->addr);
	dn_sk_ports_copy(&fl, scp);
	fl.proto = DNPROTO_NSP;
	if (dn_route_output_sock(&sk->sk_dst_cache, &fl, sk, flags) < 0)
		goto out;
	sk->sk_route_caps = sk->sk_dst_cache->dev->features;
	sock->state = SS_CONNECTING;
	scp->state = DN_CI;
	scp->segsize_loc = dst_metric(sk->sk_dst_cache, RTAX_ADVMSS);

	dn_nsp_send_conninit(sk, NSP_CI);
	err = -EINPROGRESS;
	if (*timeo) {
		err = dn_wait_run(sk, timeo);
	}
out:
	return err;
}