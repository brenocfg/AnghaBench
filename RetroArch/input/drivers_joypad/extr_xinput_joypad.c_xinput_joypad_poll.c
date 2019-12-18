#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  (* poll ) () ;} ;
struct TYPE_3__ {int connected; int /*<<< orphan*/  xstate; } ;

/* Variables and functions */
 scalar_t__ ERROR_DEVICE_NOT_CONNECTED ; 
 TYPE_2__ dinput_joypad ; 
 scalar_t__ g_XInputGetStateEx (unsigned int,int /*<<< orphan*/ *) ; 
 TYPE_1__* g_xinput_states ; 
 int /*<<< orphan*/  input_autoconfigure_disconnect (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  xinput_joypad_destroy () ; 
 int /*<<< orphan*/  xinput_joypad_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xinput_joypad_name (unsigned int) ; 

__attribute__((used)) static void xinput_joypad_poll(void)
{
   unsigned i;

   for (i = 0; i < 4; ++i)
   {
#ifdef HAVE_DINPUT
      if (g_xinput_states[i].connected)
      {
         if (g_XInputGetStateEx(i,
                  &(g_xinput_states[i].xstate))
               == ERROR_DEVICE_NOT_CONNECTED)
         {
            g_xinput_states[i].connected = false;
            input_autoconfigure_disconnect(i, xinput_joypad_name(i));
         }
      }
#else
      /* Normally, dinput handles device insertion/removal for us, but
       * since dinput is not available on UWP we have to do it ourselves */
      /* Also note that on UWP, the controllers are not available on startup
       * and are instead 'plugged in' a moment later because Microsoft reasons */
      /* TODO: This may be bad for performance? */
      bool new_connected = g_XInputGetStateEx(i, &(g_xinput_states[i].xstate)) != ERROR_DEVICE_NOT_CONNECTED;
      if (new_connected != g_xinput_states[i].connected)
      {
         if (new_connected)
         {
            /* This is kinda ugly, but it's the same thing that dinput does */
            xinput_joypad_destroy();
            xinput_joypad_init(NULL);
            return;
         }

         g_xinput_states[i].connected = new_connected;
         if (!g_xinput_states[i].connected)
            input_autoconfigure_disconnect(i, xinput_joypad_name(i));
      }
#endif
   }

#ifdef HAVE_DINPUT
   dinput_joypad.poll();
#endif
}