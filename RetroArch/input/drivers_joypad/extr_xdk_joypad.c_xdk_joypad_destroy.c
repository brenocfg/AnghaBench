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
typedef  int /*<<< orphan*/  xinput_joypad_state ;

/* Variables and functions */
 unsigned int DEFAULT_MAX_PADS ; 
 int /*<<< orphan*/  XInputClose (scalar_t__) ; 
 int /*<<< orphan*/ * g_xinput_states ; 
 scalar_t__* gamepads ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void xdk_joypad_destroy(void)
{
   unsigned i;

   for (i = 0; i < DEFAULT_MAX_PADS; i++)
   {
      memset(&g_xinput_states[i], 0, sizeof(xinput_joypad_state));
#if defined(_XBOX1)
      if (gamepads[i])
         XInputClose(gamepads[i]);
      gamepads[i]  = 0;
#endif
   }
}