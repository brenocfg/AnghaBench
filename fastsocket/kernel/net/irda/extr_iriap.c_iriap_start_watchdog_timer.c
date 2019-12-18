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
struct iriap_cb {int /*<<< orphan*/  watchdog_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  irda_start_timer (int /*<<< orphan*/ *,int,struct iriap_cb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iriap_watchdog_timer_expired ; 

__attribute__((used)) static inline void iriap_start_watchdog_timer(struct iriap_cb *self,
					      int timeout)
{
	irda_start_timer(&self->watchdog_timer, timeout, self,
			 iriap_watchdog_timer_expired);
}