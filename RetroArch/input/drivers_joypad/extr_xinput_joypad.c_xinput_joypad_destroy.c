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
typedef  int /*<<< orphan*/  xinput_joypad_state ;
struct TYPE_2__ {int /*<<< orphan*/  (* destroy ) () ;} ;

/* Variables and functions */
 TYPE_1__ dinput_joypad ; 
 int /*<<< orphan*/  dylib_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_XInputGetStateEx ; 
 int /*<<< orphan*/ * g_XInputSetState ; 
 int g_xinput_block_pads ; 
 int /*<<< orphan*/ * g_xinput_dll ; 
 int /*<<< orphan*/ * g_xinput_states ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static void xinput_joypad_destroy(void)
{
   unsigned i;

   for (i = 0; i < 4; ++i)
      memset(&g_xinput_states[i], 0, sizeof(xinput_joypad_state));

#if defined(HAVE_DYNAMIC) && !defined(__WINRT__)
   dylib_close(g_xinput_dll);

   g_xinput_dll        = NULL;
#endif
   g_XInputGetStateEx  = NULL;
   g_XInputSetState    = NULL;

#ifdef HAVE_DINPUT
   dinput_joypad.destroy();

   g_xinput_block_pads = false;
#endif
}