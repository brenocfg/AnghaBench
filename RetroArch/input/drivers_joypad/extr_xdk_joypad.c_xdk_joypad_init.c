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
 unsigned int MAX_USERS ; 
 int /*<<< orphan*/  XInitDevices (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdk_joypad_autodetect_add (unsigned int) ; 

__attribute__((used)) static bool xdk_joypad_init(void *data)
{
#ifdef _XBOX1
   XInitDevices(0, NULL);
#else
   unsigned autoconf_pad;
   for (autoconf_pad = 0; autoconf_pad < MAX_USERS; autoconf_pad++)
      xdk_joypad_autodetect_add(autoconf_pad);
#endif

   (void)data;

   return true;
}