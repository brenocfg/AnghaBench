#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sock {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  condition; } ;

/* Variables and functions */
 int /*<<< orphan*/  NR_COND_PEER_RX_BUSY ; 
 int /*<<< orphan*/  bh_lock_sock (struct sock*) ; 
 int /*<<< orphan*/  bh_unlock_sock (struct sock*) ; 
 TYPE_1__* nr_sk (struct sock*) ; 

__attribute__((used)) static void nr_t4timer_expiry(unsigned long param)
{
	struct sock *sk = (struct sock *)param;

	bh_lock_sock(sk);
	nr_sk(sk)->condition &= ~NR_COND_PEER_RX_BUSY;
	bh_unlock_sock(sk);
}