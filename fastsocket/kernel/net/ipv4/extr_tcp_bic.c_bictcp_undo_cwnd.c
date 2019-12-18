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
typedef  int /*<<< orphan*/  u32 ;
struct tcp_sock {int /*<<< orphan*/  snd_cwnd; } ;
struct sock {int dummy; } ;
struct bictcp {int /*<<< orphan*/  loss_cwnd; } ;

/* Variables and functions */
 struct bictcp* inet_csk_ca (struct sock*) ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 

__attribute__((used)) static u32 bictcp_undo_cwnd(struct sock *sk)
{
	const struct tcp_sock *tp = tcp_sk(sk);
	const struct bictcp *ca = inet_csk_ca(sk);
	return max(tp->snd_cwnd, ca->loss_cwnd);
}