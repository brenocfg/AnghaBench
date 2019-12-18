#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int pra; } ;
struct TYPE_4__ {scalar_t__ expires; } ;

/* Variables and functions */
 int DSKRDY ; 
 int HZ ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 TYPE_2__ ciaa ; 
 int /*<<< orphan*/  complete_all (int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  motor_on_completion ; 
 TYPE_1__ motor_on_timer ; 
 scalar_t__ on_attempts ; 

__attribute__((used)) static void motor_on_callback(unsigned long nr)
{
	if (!(ciaa.pra & DSKRDY) || --on_attempts == 0) {
		complete_all(&motor_on_completion);
	} else {
		motor_on_timer.expires = jiffies + HZ/10;
		add_timer(&motor_on_timer);
	}
}