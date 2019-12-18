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
struct nr_sock {int condition; } ;

/* Variables and functions */
 int NR_COND_ACK_PENDING ; 
 int /*<<< orphan*/  bh_lock_sock (struct sock*) ; 
 int /*<<< orphan*/  bh_unlock_sock (struct sock*) ; 
 int /*<<< orphan*/  nr_enquiry_response (struct sock*) ; 
 struct nr_sock* nr_sk (struct sock*) ; 

__attribute__((used)) static void nr_t2timer_expiry(unsigned long param)
{
	struct sock *sk = (struct sock *)param;
	struct nr_sock *nr = nr_sk(sk);

	bh_lock_sock(sk);
	if (nr->condition & NR_COND_ACK_PENDING) {
		nr->condition &= ~NR_COND_ACK_PENDING;
		nr_enquiry_response(sk);
	}
	bh_unlock_sock(sk);
}