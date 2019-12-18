#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sock {int /*<<< orphan*/  sk_write_space; int /*<<< orphan*/  sk_state; } ;
struct request_sock {int dummy; } ;
struct inet_connection_sock {int /*<<< orphan*/  icsk_accept_queue; scalar_t__ icsk_probes_out; scalar_t__ icsk_backoff; scalar_t__ icsk_retransmits; int /*<<< orphan*/ * icsk_bind_hash; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_4__ {int /*<<< orphan*/  loc_port; int /*<<< orphan*/  rmt_port; } ;
struct TYPE_3__ {int /*<<< orphan*/  sport; int /*<<< orphan*/  num; int /*<<< orphan*/  dport; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCP_SYN_RECV ; 
 struct inet_connection_sock* inet_csk (struct sock*) ; 
 TYPE_2__* inet_rsk (struct request_sock const*) ; 
 TYPE_1__* inet_sk (struct sock*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  security_inet_csk_clone (struct sock*,struct request_sock const*) ; 
 struct sock* sk_clone (struct sock*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  sk_stream_write_space ; 

struct sock *inet_csk_clone(struct sock *sk, const struct request_sock *req,
			    const gfp_t priority)
{
	struct sock *newsk = sk_clone(sk, priority);

	if (newsk != NULL) {
		struct inet_connection_sock *newicsk = inet_csk(newsk);

		newsk->sk_state = TCP_SYN_RECV;
		newicsk->icsk_bind_hash = NULL;

		inet_sk(newsk)->dport = inet_rsk(req)->rmt_port;
		inet_sk(newsk)->num = ntohs(inet_rsk(req)->loc_port);
		inet_sk(newsk)->sport = inet_rsk(req)->loc_port;
		newsk->sk_write_space = sk_stream_write_space;

		newicsk->icsk_retransmits = 0;
		newicsk->icsk_backoff	  = 0;
		newicsk->icsk_probes_out  = 0;

		/* Deinitialize accept_queue to trap illegal accesses. */
		memset(&newicsk->icsk_accept_queue, 0, sizeof(newicsk->icsk_accept_queue));

		security_inet_csk_clone(newsk, req);
	}
	return newsk;
}