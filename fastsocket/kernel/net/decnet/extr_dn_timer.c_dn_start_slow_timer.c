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
struct TYPE_2__ {unsigned long data; int /*<<< orphan*/  function; scalar_t__ expires; } ;
struct sock {TYPE_1__ sk_timer; } ;

/* Variables and functions */
 scalar_t__ SLOW_INTERVAL ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  dn_slow_timer ; 
 scalar_t__ jiffies ; 

void dn_start_slow_timer(struct sock *sk)
{
	sk->sk_timer.expires	= jiffies + SLOW_INTERVAL;
	sk->sk_timer.function	= dn_slow_timer;
	sk->sk_timer.data	= (unsigned long)sk;

	add_timer(&sk->sk_timer);
}