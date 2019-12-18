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
 int FLAG_ECE ; 
 int /*<<< orphan*/  tcp_ratehalving_spur_to_response (struct sock*) ; 
 int /*<<< orphan*/  tcp_undo_cwr (struct sock*,int) ; 

__attribute__((used)) static void tcp_undo_spur_to_response(struct sock *sk, int flag)
{
	if (flag & FLAG_ECE)
		tcp_ratehalving_spur_to_response(sk);
	else
		tcp_undo_cwr(sk, true);
}