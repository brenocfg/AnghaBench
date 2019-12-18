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
typedef  int /*<<< orphan*/  u32 ;
struct sock {int dummy; } ;
struct inet_connection_sock {TYPE_1__* icsk_ca_ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  snd_cwnd_stamp; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* cong_avoid ) (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 struct inet_connection_sock* inet_csk (struct sock*) ; 
 int /*<<< orphan*/  stub1 (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* tcp_sk (struct sock*) ; 
 int /*<<< orphan*/  tcp_time_stamp ; 

__attribute__((used)) static void tcp_cong_avoid(struct sock *sk, u32 ack, u32 in_flight)
{
	const struct inet_connection_sock *icsk = inet_csk(sk);
	icsk->icsk_ca_ops->cong_avoid(sk, ack, in_flight);
	tcp_sk(sk)->snd_cwnd_stamp = tcp_time_stamp;
}