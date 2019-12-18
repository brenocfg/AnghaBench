#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sock {int dummy; } ;
struct request_sock {int /*<<< orphan*/ * sk; TYPE_2__* rsk_ops; struct request_sock* dl_next; } ;
struct listen_sock {int /*<<< orphan*/  nr_table_entries; int /*<<< orphan*/  hash_rnd; struct request_sock** syn_table; } ;
struct TYPE_4__ {struct listen_sock* listen_opt; } ;
struct inet_connection_sock {TYPE_1__ icsk_accept_queue; } ;
struct inet6_request_sock {int const iif; int /*<<< orphan*/  loc_addr; int /*<<< orphan*/  rmt_addr; } ;
struct in6_addr {int dummy; } ;
typedef  scalar_t__ __be16 ;
struct TYPE_6__ {scalar_t__ const rmt_port; } ;
struct TYPE_5__ {scalar_t__ family; } ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 struct inet6_request_sock* inet6_rsk (struct request_sock*) ; 
 size_t inet6_synq_hash (struct in6_addr const*,scalar_t__ const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct inet_connection_sock* inet_csk (struct sock const*) ; 
 TYPE_3__* inet_rsk (struct request_sock*) ; 
 scalar_t__ ipv6_addr_equal (int /*<<< orphan*/ *,struct in6_addr const*) ; 

struct request_sock *inet6_csk_search_req(const struct sock *sk,
					  struct request_sock ***prevp,
					  const __be16 rport,
					  const struct in6_addr *raddr,
					  const struct in6_addr *laddr,
					  const int iif)
{
	const struct inet_connection_sock *icsk = inet_csk(sk);
	struct listen_sock *lopt = icsk->icsk_accept_queue.listen_opt;
	struct request_sock *req, **prev;

	for (prev = &lopt->syn_table[inet6_synq_hash(raddr, rport,
						     lopt->hash_rnd,
						     lopt->nr_table_entries)];
	     (req = *prev) != NULL;
	     prev = &req->dl_next) {
		const struct inet6_request_sock *treq = inet6_rsk(req);

		if (inet_rsk(req)->rmt_port == rport &&
		    req->rsk_ops->family == AF_INET6 &&
		    ipv6_addr_equal(&treq->rmt_addr, raddr) &&
		    ipv6_addr_equal(&treq->loc_addr, laddr) &&
		    (!treq->iif || treq->iif == iif)) {
			WARN_ON(req->sk != NULL);
			*prevp = prev;
			return req;
		}
	}

	return NULL;
}