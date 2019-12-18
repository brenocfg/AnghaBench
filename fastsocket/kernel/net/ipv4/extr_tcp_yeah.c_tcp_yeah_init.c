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
struct yeah {int reno_count; scalar_t__ lastQ; scalar_t__ doing_reno_now; } ;
struct tcp_sock {int /*<<< orphan*/  snd_cwnd_clamp; } ;
struct sock {int dummy; } ;

/* Variables and functions */
 struct yeah* inet_csk_ca (struct sock*) ; 
 int /*<<< orphan*/  min_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 int /*<<< orphan*/  tcp_vegas_init (struct sock*) ; 
 int /*<<< orphan*/  u32 ; 

__attribute__((used)) static void tcp_yeah_init(struct sock *sk)
{
	struct tcp_sock *tp = tcp_sk(sk);
	struct yeah *yeah = inet_csk_ca(sk);

	tcp_vegas_init(sk);

	yeah->doing_reno_now = 0;
	yeah->lastQ = 0;

	yeah->reno_count = 2;

	/* Ensure the MD arithmetic works.  This is somewhat pedantic,
	 * since I don't think we will see a cwnd this large. :) */
	tp->snd_cwnd_clamp = min_t(u32, tp->snd_cwnd_clamp, 0xffffffff/128);

}