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
struct irlmp_cb {int /*<<< orphan*/  discovery_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  irda_start_timer (int /*<<< orphan*/ *,int,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irlmp_discovery_timer_expired ; 

void irlmp_start_discovery_timer(struct irlmp_cb *self, int timeout)
{
	irda_start_timer(&self->discovery_timer, timeout, (void *) self,
			 irlmp_discovery_timer_expired);
}