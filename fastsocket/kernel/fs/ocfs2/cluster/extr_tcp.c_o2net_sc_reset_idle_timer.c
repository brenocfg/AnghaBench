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
struct o2net_sock_container {int /*<<< orphan*/  sc_idle_timeout; int /*<<< orphan*/  sc_tv_timer; int /*<<< orphan*/  sc_keepalive_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_gettimeofday (int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  o2net_idle_timeout () ; 
 int /*<<< orphan*/  o2net_keepalive_delay () ; 
 int /*<<< orphan*/  o2net_sc_cancel_delayed_work (struct o2net_sock_container*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  o2net_sc_queue_delayed_work (struct o2net_sock_container*,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void o2net_sc_reset_idle_timer(struct o2net_sock_container *sc)
{
	o2net_sc_cancel_delayed_work(sc, &sc->sc_keepalive_work);
	o2net_sc_queue_delayed_work(sc, &sc->sc_keepalive_work,
		      msecs_to_jiffies(o2net_keepalive_delay()));
	do_gettimeofday(&sc->sc_tv_timer);
	mod_timer(&sc->sc_idle_timeout,
	       jiffies + msecs_to_jiffies(o2net_idle_timeout()));
}