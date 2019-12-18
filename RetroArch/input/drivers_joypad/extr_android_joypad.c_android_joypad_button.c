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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct android_app {int** hat_state; } ;

/* Variables and functions */
 scalar_t__ BIT_GET (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned int DEFAULT_MAX_PADS ; 
 unsigned int GET_HAT (int /*<<< orphan*/ ) ; 
 unsigned int GET_HAT_DIR (int /*<<< orphan*/ ) ; 
#define  HAT_DOWN_MASK 131 
#define  HAT_LEFT_MASK 130 
#define  HAT_RIGHT_MASK 129 
#define  HAT_UP_MASK 128 
 int /*<<< orphan*/  LAST_KEYCODE ; 
 int /*<<< orphan*/ * android_keyboard_state_get (unsigned int) ; 
 scalar_t__ g_android ; 

__attribute__((used)) static bool android_joypad_button(unsigned port, uint16_t joykey)
{
   uint8_t *buf                    = android_keyboard_state_get(port);
   struct android_app *android_app = (struct android_app*)g_android;
   unsigned hat_dir                = GET_HAT_DIR(joykey);

   if (port >= DEFAULT_MAX_PADS)
      return false;

   if (hat_dir)
   {
      unsigned h = GET_HAT(joykey);
      if (h > 0)
         return false;

      switch (hat_dir)
      {
         case HAT_LEFT_MASK:
            return android_app->hat_state[port][0] == -1;
         case HAT_RIGHT_MASK:
            return android_app->hat_state[port][0] ==  1;
         case HAT_UP_MASK:
            return android_app->hat_state[port][1] == -1;
         case HAT_DOWN_MASK:
            return android_app->hat_state[port][1] ==  1;
         default:
            return false;
      }
   }

   return joykey < LAST_KEYCODE && BIT_GET(buf, joykey);
}