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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_EVENT_QUIT ; 
 int PANIC_BUTTON_MASK ; 
 int /*<<< orphan*/  command_event (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void check_panic_button(uint32_t held_buttons)
{
   if ((held_buttons & PANIC_BUTTON_MASK) == PANIC_BUTTON_MASK)
      command_event(CMD_EVENT_QUIT, NULL);
}