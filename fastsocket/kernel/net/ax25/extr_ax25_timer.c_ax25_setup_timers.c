#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  idletimer; int /*<<< orphan*/  t3timer; int /*<<< orphan*/  t2timer; int /*<<< orphan*/  t1timer; int /*<<< orphan*/  timer; } ;
typedef  TYPE_1__ ax25_cb ;

/* Variables and functions */
 int /*<<< orphan*/  ax25_heartbeat_expiry ; 
 int /*<<< orphan*/  ax25_idletimer_expiry ; 
 int /*<<< orphan*/  ax25_t1timer_expiry ; 
 int /*<<< orphan*/  ax25_t2timer_expiry ; 
 int /*<<< orphan*/  ax25_t3timer_expiry ; 
 int /*<<< orphan*/  setup_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 

void ax25_setup_timers(ax25_cb *ax25)
{
	setup_timer(&ax25->timer, ax25_heartbeat_expiry, (unsigned long)ax25);
	setup_timer(&ax25->t1timer, ax25_t1timer_expiry, (unsigned long)ax25);
	setup_timer(&ax25->t2timer, ax25_t2timer_expiry, (unsigned long)ax25);
	setup_timer(&ax25->t3timer, ax25_t3timer_expiry, (unsigned long)ax25);
	setup_timer(&ax25->idletimer, ax25_idletimer_expiry,
		    (unsigned long)ax25);
}