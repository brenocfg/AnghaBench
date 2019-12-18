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
struct tcp_sock {int snd_ssthresh; int /*<<< orphan*/  snd_cwnd; } ;
struct sock {int dummy; } ;
struct htcp {int beta; scalar_t__ undo_last_cong; int /*<<< orphan*/  undo_old_maxB; int /*<<< orphan*/  old_maxB; int /*<<< orphan*/  undo_maxRTT; int /*<<< orphan*/  maxRTT; scalar_t__ last_cong; } ;

/* Variables and functions */
 struct htcp* inet_csk_ca (struct sock*) ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,int) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 

__attribute__((used)) static u32 htcp_cwnd_undo(struct sock *sk)
{
	const struct tcp_sock *tp = tcp_sk(sk);
	struct htcp *ca = inet_csk_ca(sk);

	if (ca->undo_last_cong) {
		ca->last_cong = ca->undo_last_cong;
		ca->maxRTT = ca->undo_maxRTT;
		ca->old_maxB = ca->undo_old_maxB;
		ca->undo_last_cong = 0;
	}

	return max(tp->snd_cwnd, (tp->snd_ssthresh << 7) / ca->beta);
}