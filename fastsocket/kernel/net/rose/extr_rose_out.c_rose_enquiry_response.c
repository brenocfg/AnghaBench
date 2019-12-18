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
struct rose_sock {int condition; int /*<<< orphan*/  vr; int /*<<< orphan*/  vl; } ;

/* Variables and functions */
 int ROSE_COND_ACK_PENDING ; 
 int ROSE_COND_OWN_RX_BUSY ; 
 int /*<<< orphan*/  ROSE_RNR ; 
 int /*<<< orphan*/  ROSE_RR ; 
 struct rose_sock* rose_sk (struct sock*) ; 
 int /*<<< orphan*/  rose_stop_timer (struct sock*) ; 
 int /*<<< orphan*/  rose_write_internal (struct sock*,int /*<<< orphan*/ ) ; 

void rose_enquiry_response(struct sock *sk)
{
	struct rose_sock *rose = rose_sk(sk);

	if (rose->condition & ROSE_COND_OWN_RX_BUSY)
		rose_write_internal(sk, ROSE_RNR);
	else
		rose_write_internal(sk, ROSE_RR);

	rose->vl         = rose->vr;
	rose->condition &= ~ROSE_COND_ACK_PENDING;

	rose_stop_timer(sk);
}