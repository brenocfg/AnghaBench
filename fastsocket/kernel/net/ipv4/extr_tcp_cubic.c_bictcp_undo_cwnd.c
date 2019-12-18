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
typedef  int /*<<< orphan*/  u32 ;
struct sock {int dummy; } ;
struct bictcp {int /*<<< orphan*/  loss_cwnd; } ;
struct TYPE_2__ {int /*<<< orphan*/  snd_cwnd; } ;

/* Variables and functions */
 struct bictcp* inet_csk_ca (struct sock*) ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* tcp_sk (struct sock*) ; 

__attribute__((used)) static u32 bictcp_undo_cwnd(struct sock *sk)
{
	struct bictcp *ca = inet_csk_ca(sk);

	return max(tcp_sk(sk)->snd_cwnd, ca->loss_cwnd);
}