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
struct mirror_set {TYPE_1__ timer; int /*<<< orphan*/  timer_pending; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  delayed_wake_fn ; 
 scalar_t__ jiffies ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void delayed_wake(struct mirror_set *ms)
{
	if (test_and_set_bit(0, &ms->timer_pending))
		return;

	ms->timer.expires = jiffies + HZ / 5;
	ms->timer.data = (unsigned long) ms;
	ms->timer.function = delayed_wake_fn;
	add_timer(&ms->timer);
}