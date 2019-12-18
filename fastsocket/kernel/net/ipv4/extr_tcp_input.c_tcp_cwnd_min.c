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
struct tcp_congestion_ops {int /*<<< orphan*/  (* min_cwnd ) (struct sock const*) ;} ;
struct sock {int dummy; } ;
struct TYPE_4__ {struct tcp_congestion_ops* icsk_ca_ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  snd_ssthresh; } ;

/* Variables and functions */
 TYPE_2__* inet_csk (struct sock const*) ; 
 int /*<<< orphan*/  stub1 (struct sock const*) ; 
 TYPE_1__* tcp_sk (struct sock const*) ; 

__attribute__((used)) static inline u32 tcp_cwnd_min(const struct sock *sk)
{
	const struct tcp_congestion_ops *ca_ops = inet_csk(sk)->icsk_ca_ops;

	return ca_ops->min_cwnd ? ca_ops->min_cwnd(sk) : tcp_sk(sk)->snd_ssthresh;
}