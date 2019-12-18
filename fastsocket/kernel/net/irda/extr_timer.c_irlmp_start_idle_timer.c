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
struct lap_cb {int /*<<< orphan*/  idle_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  irda_start_timer (int /*<<< orphan*/ *,int,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irlmp_idle_timer_expired ; 

void irlmp_start_idle_timer(struct lap_cb *self, int timeout)
{
	irda_start_timer(&self->idle_timer, timeout, (void *) self,
			 irlmp_idle_timer_expired);
}