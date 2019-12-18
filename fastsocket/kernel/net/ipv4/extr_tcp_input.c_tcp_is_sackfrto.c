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
struct tcp_sock {int dummy; } ;

/* Variables and functions */
 int sysctl_tcp_frto ; 
 int /*<<< orphan*/  tcp_is_reno (struct tcp_sock const*) ; 

__attribute__((used)) static int tcp_is_sackfrto(const struct tcp_sock *tp)
{
	return (sysctl_tcp_frto == 0x2) && !tcp_is_reno(tp);
}