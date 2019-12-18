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
struct sock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipv4_rcv_saddr_equal ; 
 int udp_lib_get_port (struct sock*,unsigned short,int /*<<< orphan*/ ) ; 

int udp_v4_get_port(struct sock *sk, unsigned short snum)
{
	return udp_lib_get_port(sk, snum, ipv4_rcv_saddr_equal);
}