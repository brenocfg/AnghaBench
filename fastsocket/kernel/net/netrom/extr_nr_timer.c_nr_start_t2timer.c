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
struct nr_sock {scalar_t__ t2; int /*<<< orphan*/  t2timer; } ;

/* Variables and functions */
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 struct nr_sock* nr_sk (struct sock*) ; 

void nr_start_t2timer(struct sock *sk)
{
	struct nr_sock *nr = nr_sk(sk);

	mod_timer(&nr->t2timer, jiffies + nr->t2);
}