#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ old_led_state; } ;
typedef  TYPE_1__ hfcusb_data ;
typedef  scalar_t__ __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  HFCUSB_P_DATA ; 
 int /*<<< orphan*/  queue_control_request (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static void
write_led(hfcusb_data * hfc, __u8 led_state)
{
	if (led_state != hfc->old_led_state) {
		hfc->old_led_state = led_state;
		queue_control_request(hfc, HFCUSB_P_DATA, led_state, 1);
	}
}