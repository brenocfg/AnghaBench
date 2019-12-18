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
typedef  int /*<<< orphan*/  uwp_input_t ;
struct retro_keybind {int dummy; } ;
typedef  int /*<<< orphan*/  rarch_joypad_info_t ;
typedef  int int16_t ;

/* Variables and functions */
 unsigned int RARCH_BIND_LIST_END ; 
#define  RARCH_DEVICE_MOUSE_SCREEN 134 
#define  RARCH_DEVICE_POINTER_SCREEN 133 
 unsigned int RARCH_FIRST_CUSTOM_BIND ; 
 unsigned int RETROK_LAST ; 
#define  RETRO_DEVICE_ANALOG 132 
 unsigned int RETRO_DEVICE_ID_JOYPAD_MASK ; 
#define  RETRO_DEVICE_JOYPAD 131 
#define  RETRO_DEVICE_KEYBOARD 130 
#define  RETRO_DEVICE_MOUSE 129 
#define  RETRO_DEVICE_POINTER 128 
 int /*<<< orphan*/  uwp_keyboard_pressed (unsigned int) ; 
 int uwp_mouse_state (unsigned int,unsigned int,int) ; 
 int uwp_pointer_state (unsigned int,unsigned int,int) ; 
 int uwp_pressed_analog (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct retro_keybind const*,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  uwp_pressed_joypad (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct retro_keybind const*,unsigned int,unsigned int) ; 

__attribute__((used)) static int16_t uwp_input_state(void *data,
      rarch_joypad_info_t joypad_info,
      const struct retro_keybind **binds,
      unsigned port, unsigned device,
      unsigned index, unsigned id)
{
   uwp_input_t *uwp           = (uwp_input_t*)data;

   switch (device)
   {
      case RETRO_DEVICE_JOYPAD:
         if (id == RETRO_DEVICE_ID_JOYPAD_MASK)
         {
            unsigned i;
            int16_t ret = 0;
            for (i = 0; i < RARCH_FIRST_CUSTOM_BIND; i++)
            {
               if (uwp_pressed_joypad(
                        uwp, joypad_info, binds[port], port, i))
               {
                  ret |= (1 << i);
                  continue;
               }
            }

            return ret;
         }
         else
         {
            if (id < RARCH_BIND_LIST_END)
               if (uwp_pressed_joypad(uwp, joypad_info, binds[port], port, id))
                  return true;
         }
         break;
      case RETRO_DEVICE_ANALOG:
         if (binds[port])
            return uwp_pressed_analog(uwp, joypad_info, binds[port], port, index, id);
      case RETRO_DEVICE_KEYBOARD:
         return (id < RETROK_LAST) && uwp_keyboard_pressed(id);

      case RETRO_DEVICE_MOUSE:
      case RARCH_DEVICE_MOUSE_SCREEN:
         return uwp_mouse_state(port, id, device == RARCH_DEVICE_MOUSE_SCREEN);

      case RETRO_DEVICE_POINTER:
      case RARCH_DEVICE_POINTER_SCREEN:
         return uwp_pointer_state(index, id, device == RARCH_DEVICE_POINTER_SCREEN);
   }

   return 0;
}