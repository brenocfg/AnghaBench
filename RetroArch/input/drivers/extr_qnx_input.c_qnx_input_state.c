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
struct retro_keybind {int dummy; } ;
typedef  int /*<<< orphan*/  rarch_joypad_info_t ;
typedef  int /*<<< orphan*/  qnx_input_t ;
typedef  int int16_t ;

/* Variables and functions */
#define  RARCH_DEVICE_POINTER_SCREEN 131 
 unsigned int RARCH_FIRST_CUSTOM_BIND ; 
 unsigned int RETRO_DEVICE_ID_JOYPAD_MASK ; 
#define  RETRO_DEVICE_JOYPAD 130 
#define  RETRO_DEVICE_KEYBOARD 129 
#define  RETRO_DEVICE_POINTER 128 
 int /*<<< orphan*/  qnx_is_pressed (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,struct retro_keybind const*,unsigned int) ; 
 int qnx_keyboard_pressed (int /*<<< orphan*/ *,unsigned int) ; 
 int qnx_pointer_input_state (int /*<<< orphan*/ *,unsigned int,unsigned int,int) ; 

__attribute__((used)) static int16_t qnx_input_state(void *data,
      rarch_joypad_info_t joypad_info,
      const struct retro_keybind **binds,
      unsigned port, unsigned device, unsigned idx, unsigned id)
{
   qnx_input_t *qnx           = (qnx_input_t*)data;

   switch (device)
   {
      case RETRO_DEVICE_JOYPAD:
         if (id == RETRO_DEVICE_ID_JOYPAD_MASK)
         {
            unsigned i;
            int16_t ret = 0;
            for (i = 0; i < RARCH_FIRST_CUSTOM_BIND; i++)
            {
               if (qnx_is_pressed(
                        qnx, joypad_info, port, binds[port], i))
               {
                  ret |= (1 << i);
                  continue;
               }
            }

            return ret;
         }
         else
            if (qnx_is_pressed(qnx, joypad_info, port, binds[port], id))
               return true;
         break;
      case RETRO_DEVICE_KEYBOARD:
         return qnx_keyboard_pressed(qnx, id);
      case RETRO_DEVICE_POINTER:
      case RARCH_DEVICE_POINTER_SCREEN:
         return qnx_pointer_input_state(qnx, idx, id, device == RARCH_DEVICE_POINTER_SCREEN);
      default:
          break;
   }

   return 0;
}