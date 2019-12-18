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
struct dinput_input {struct dinput_input* joypad_driver_name; scalar_t__ mouse; scalar_t__ keyboard; TYPE_1__* joypad; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* destroy ) () ;} ;
typedef  int /*<<< orphan*/ * LPDIRECTINPUT8 ;

/* Variables and functions */
 int /*<<< orphan*/  IDirectInputDevice8_Release (scalar_t__) ; 
 int /*<<< orphan*/  dinput_clear_pointers (struct dinput_input*) ; 
 int /*<<< orphan*/  dinput_destroy_context () ; 
 int /*<<< orphan*/  free (struct dinput_input*) ; 
 int /*<<< orphan*/ * g_dinput_ctx ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static void dinput_free(void *data)
{
   struct dinput_input *di = (struct dinput_input*)data;
   LPDIRECTINPUT8 hold_ctx = g_dinput_ctx;

   if (di)
   {
      /* Prevent a joypad driver to kill our context prematurely. */
      g_dinput_ctx = NULL;
      if (di->joypad)
         di->joypad->destroy();
      g_dinput_ctx = hold_ctx;

      /* Clear any leftover pointers. */
      dinput_clear_pointers(di);

      if (di->keyboard)
         IDirectInputDevice8_Release(di->keyboard);

      if (di->mouse)
         IDirectInputDevice8_Release(di->mouse);

      if (di->joypad_driver_name)
         free(di->joypad_driver_name);

      free(di);
   }

   dinput_destroy_context();
}