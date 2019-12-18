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
typedef  int /*<<< orphan*/  uint16_t ;
struct linuxraw_joypad {int /*<<< orphan*/  buttons; } ;

/* Variables and functions */
 scalar_t__ BIT32_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NUM_BUTTONS ; 
 int /*<<< orphan*/ * linuxraw_pads ; 

__attribute__((used)) static bool linuxraw_joypad_button(unsigned port, uint16_t joykey)
{
   const struct linuxraw_joypad *pad = (const struct linuxraw_joypad*)
      &linuxraw_pads[port];

   return joykey < NUM_BUTTONS && BIT32_GET(pad->buttons, joykey);
}