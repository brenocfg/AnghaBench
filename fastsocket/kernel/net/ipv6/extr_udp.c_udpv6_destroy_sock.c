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
 int /*<<< orphan*/  inet6_destroy_sock (struct sock*) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  udp_v6_flush_pending_frames (struct sock*) ; 

void udpv6_destroy_sock(struct sock *sk)
{
	lock_sock(sk);
	udp_v6_flush_pending_frames(sk);
	release_sock(sk);

	inet6_destroy_sock(sk);
}