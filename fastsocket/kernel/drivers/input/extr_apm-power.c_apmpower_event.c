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
struct input_handle {int dummy; } ;

/* Variables and functions */
#define  EV_PWR 128 
 int /*<<< orphan*/  system_power_event (unsigned int) ; 

__attribute__((used)) static void apmpower_event(struct input_handle *handle, unsigned int type,
		        unsigned int code, int value)
{
	/* only react on key down events */
	if (value != 1)
		return;

	switch (type) {
	case EV_PWR:
		system_power_event(code);
		break;

	default:
		break;
	}
}