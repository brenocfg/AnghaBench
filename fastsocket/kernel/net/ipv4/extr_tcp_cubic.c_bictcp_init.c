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
struct sock {int dummy; } ;
struct bictcp {scalar_t__ loss_cwnd; } ;
struct TYPE_2__ {scalar_t__ snd_ssthresh; } ;

/* Variables and functions */
 int /*<<< orphan*/  bictcp_hystart_reset (struct sock*) ; 
 int /*<<< orphan*/  bictcp_reset (struct bictcp*) ; 
 scalar_t__ hystart ; 
 struct bictcp* inet_csk_ca (struct sock*) ; 
 scalar_t__ initial_ssthresh ; 
 TYPE_1__* tcp_sk (struct sock*) ; 

__attribute__((used)) static void bictcp_init(struct sock *sk)
{
	struct bictcp *ca = inet_csk_ca(sk);

	bictcp_reset(ca);
	ca->loss_cwnd = 0;

	if (hystart)
		bictcp_hystart_reset(sk);

	if (!hystart && initial_ssthresh)
		tcp_sk(sk)->snd_ssthresh = initial_ssthresh;
}