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
struct tcp_sock {scalar_t__ sacked_out; scalar_t__ fackets_out; } ;

/* Variables and functions */
 int /*<<< orphan*/  tcp_clear_retrans_partial (struct tcp_sock*) ; 

void tcp_clear_retrans(struct tcp_sock *tp)
{
	tcp_clear_retrans_partial(tp);

	tp->fackets_out = 0;
	tp->sacked_out = 0;
}