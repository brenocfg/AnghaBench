#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ expires; scalar_t__ data; int /*<<< orphan*/  function; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 scalar_t__ cmm_timed_pages_target ; 
 int cmm_timeout_seconds ; 
 TYPE_1__ cmm_timer ; 
 int /*<<< orphan*/  cmm_timer_fn ; 
 int /*<<< orphan*/  del_timer (TYPE_1__*) ; 
 scalar_t__ jiffies ; 
 scalar_t__ mod_timer (TYPE_1__*,scalar_t__) ; 
 scalar_t__ timer_pending (TYPE_1__*) ; 

__attribute__((used)) static void
cmm_set_timer(void)
{
	if (cmm_timed_pages_target <= 0 || cmm_timeout_seconds <= 0) {
		if (timer_pending(&cmm_timer))
			del_timer(&cmm_timer);
		return;
	}
	if (timer_pending(&cmm_timer)) {
		if (mod_timer(&cmm_timer, jiffies + cmm_timeout_seconds*HZ))
			return;
	}
	cmm_timer.function = cmm_timer_fn;
	cmm_timer.data = 0;
	cmm_timer.expires = jiffies + cmm_timeout_seconds*HZ;
	add_timer(&cmm_timer);
}