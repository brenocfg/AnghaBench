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

/* Variables and functions */
 int /*<<< orphan*/  dos_joypad_autodetect_add (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hook_keyb_int () ; 

__attribute__((used)) static bool dos_joypad_init(void *data)
{
   hook_keyb_int();

   dos_joypad_autodetect_add(0);

   (void)data;

   return true;
}