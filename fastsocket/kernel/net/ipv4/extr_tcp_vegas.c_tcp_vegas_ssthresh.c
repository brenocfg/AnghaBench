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
struct tcp_sock {scalar_t__ snd_cwnd; int /*<<< orphan*/  snd_ssthresh; } ;

/* Variables and functions */
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline u32 tcp_vegas_ssthresh(struct tcp_sock *tp)
{
	return  min(tp->snd_ssthresh, tp->snd_cwnd-1);
}