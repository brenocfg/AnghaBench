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
struct TYPE_2__ {scalar_t__ state; } ;
struct max3100_port {scalar_t__ poll_time; int /*<<< orphan*/  timer; TYPE_1__ port; } ;

/* Variables and functions */
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  max3100_dowork (struct max3100_port*) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void max3100_timeout(unsigned long data)
{
	struct max3100_port *s = (struct max3100_port *)data;

	if (s->port.state) {
		max3100_dowork(s);
		mod_timer(&s->timer, jiffies + s->poll_time);
	}
}