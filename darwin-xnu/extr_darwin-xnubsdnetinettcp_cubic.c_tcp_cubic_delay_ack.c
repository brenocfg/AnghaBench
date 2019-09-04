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
struct tcphdr {int dummy; } ;
struct tcpcb {int dummy; } ;

/* Variables and functions */
 int tcp_cc_delay_ack (struct tcpcb*,struct tcphdr*) ; 

__attribute__((used)) static int
tcp_cubic_delay_ack(struct tcpcb *tp, struct tcphdr *th)
{
	return (tcp_cc_delay_ack(tp, th));
}