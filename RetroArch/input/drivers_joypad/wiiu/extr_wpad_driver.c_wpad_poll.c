#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  hold; } ;
typedef  TYPE_1__ VPADStatus ;
typedef  scalar_t__ VPADReadError ;

/* Variables and functions */
 int /*<<< orphan*/  PAD_GAMEPAD ; 
 int /*<<< orphan*/  VPADRead (int /*<<< orphan*/ ,TYPE_1__*,int,scalar_t__*) ; 
 int /*<<< orphan*/  analog_state ; 
 int /*<<< orphan*/  button_state ; 
 int /*<<< orphan*/  check_panic_button (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_analog_state (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  update_button_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_touch_state (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void wpad_poll(void)
{
   VPADStatus vpad;
   VPADReadError error;

   VPADRead(PAD_GAMEPAD, &vpad, 1, &error);

   if (error)
      return;

   update_button_state(&button_state, vpad.hold);
   update_analog_state(analog_state, &vpad);
   update_touch_state(analog_state, &button_state, &vpad);
   check_panic_button(vpad.hold);
}