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
struct veno {scalar_t__ diff; } ;
struct tcp_sock {int snd_cwnd; } ;
struct sock {int dummy; } ;

/* Variables and functions */
 scalar_t__ beta ; 
 struct veno* inet_csk_ca (struct sock*) ; 
 int /*<<< orphan*/  max (unsigned int,unsigned int) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 

__attribute__((used)) static u32 tcp_veno_ssthresh(struct sock *sk)
{
	const struct tcp_sock *tp = tcp_sk(sk);
	struct veno *veno = inet_csk_ca(sk);

	if (veno->diff < beta)
		/* in "non-congestive state", cut cwnd by 1/5 */
		return max(tp->snd_cwnd * 4 / 5, 2U);
	else
		/* in "congestive state", cut cwnd by 1/2 */
		return max(tp->snd_cwnd >> 1U, 2U);
}