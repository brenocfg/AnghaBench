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
typedef  scalar_t__ u8 ;
struct sock {int dummy; } ;
struct illinois {scalar_t__ rtt_above; scalar_t__ rtt_low; int /*<<< orphan*/  beta; int /*<<< orphan*/  alpha; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALPHA_BASE ; 
 int /*<<< orphan*/  BETA_BASE ; 
 scalar_t__ TCP_CA_Loss ; 
 struct illinois* inet_csk_ca (struct sock*) ; 
 int /*<<< orphan*/  rtt_reset (struct sock*) ; 

__attribute__((used)) static void tcp_illinois_state(struct sock *sk, u8 new_state)
{
	struct illinois *ca = inet_csk_ca(sk);

	if (new_state == TCP_CA_Loss) {
		ca->alpha = ALPHA_BASE;
		ca->beta = BETA_BASE;
		ca->rtt_low = 0;
		ca->rtt_above = 0;
		rtt_reset(sk);
	}
}