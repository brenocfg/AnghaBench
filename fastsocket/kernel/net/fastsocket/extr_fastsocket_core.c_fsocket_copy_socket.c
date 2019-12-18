#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct socket {TYPE_5__* sk; } ;
struct TYPE_12__ {int /*<<< orphan*/  pingpong; } ;
struct TYPE_11__ {int /*<<< orphan*/  rskq_defer_accept; } ;
struct TYPE_16__ {TYPE_3__ icsk_ack; TYPE_2__ icsk_accept_queue; } ;
struct TYPE_15__ {int /*<<< orphan*/  transparent; int /*<<< orphan*/  freebind; } ;
struct TYPE_14__ {int /*<<< orphan*/  sk_lingertime; int /*<<< orphan*/  sk_reuse; int /*<<< orphan*/  sk_flags; } ;
struct TYPE_10__ {int /*<<< orphan*/  user_mss; } ;
struct TYPE_13__ {TYPE_1__ rx_opt; } ;

/* Variables and functions */
 TYPE_8__* inet_csk (TYPE_5__*) ; 
 TYPE_6__* inet_sk (TYPE_5__*) ; 
 TYPE_4__* tcp_sk (TYPE_5__*) ; 

__attribute__((used)) static void fsocket_copy_socket(struct socket *oldsock, struct socket *newsock)
{
	//TODO: Check if all these copy works.

	/* General sk flags */
	newsock->sk->sk_flags = oldsock->sk->sk_flags;
	/* Non-Block */

	/* REUSEADDR (Verified) */
	newsock->sk->sk_reuse = oldsock->sk->sk_reuse;
	/* LINGER */
	newsock->sk->sk_lingertime = oldsock->sk->sk_lingertime;
	/* TPROXY - IP_TRANSPARENT and IP_FREEBIND */
	inet_sk(newsock->sk)->freebind = inet_sk(oldsock->sk)->freebind;
	inet_sk(newsock->sk)->transparent = inet_sk(oldsock->sk)->transparent;
	/* TCP_MAXSEG */
	tcp_sk(newsock->sk)->rx_opt.user_mss = tcp_sk(oldsock->sk)->rx_opt.user_mss;
	/* TCP_DEFER_ACCEPT */
	inet_csk(newsock->sk)->icsk_accept_queue.rskq_defer_accept =
		inet_csk(oldsock->sk)->icsk_accept_queue.rskq_defer_accept;
	/* TCP_QUICKACK */
	inet_csk(newsock->sk)->icsk_ack.pingpong = inet_csk(oldsock->sk)->icsk_ack.pingpong;

	//TODO: Other attibutes that need to be copied
}