#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct retro_keybind {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  mouse; int /*<<< orphan*/  joypad; } ;
typedef  TYPE_1__ rwebinput_input_t ;
typedef  int /*<<< orphan*/  rarch_joypad_info_t ;
typedef  int int16_t ;

/* Variables and functions */
 unsigned int RARCH_BIND_LIST_END ; 
#define  RARCH_DEVICE_MOUSE_SCREEN 134 
#define  RARCH_DEVICE_POINTER_SCREEN 133 
 unsigned int RARCH_FIRST_CUSTOM_BIND ; 
#define  RETRO_DEVICE_ANALOG 132 
 unsigned int RETRO_DEVICE_ID_JOYPAD_MASK ; 
#define  RETRO_DEVICE_JOYPAD 131 
#define  RETRO_DEVICE_KEYBOARD 130 
#define  RETRO_DEVICE_MOUSE 129 
#define  RETRO_DEVICE_POINTER 128 
 int input_joypad_analog (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int,struct retro_keybind const*) ; 
 int rwebinput_analog_pressed (TYPE_1__*,int /*<<< orphan*/ ,struct retro_keybind const*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  rwebinput_is_pressed (TYPE_1__*,int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int) ; 
 int rwebinput_key_pressed (TYPE_1__*,unsigned int) ; 
 int rwebinput_mouse_state (int /*<<< orphan*/ *,unsigned int,int) ; 
 int rwebinput_pointer_device_state (int /*<<< orphan*/ *,unsigned int,int) ; 

__attribute__((used)) static int16_t rwebinput_input_state(void *data,
      rarch_joypad_info_t joypad_info,
      const struct retro_keybind **binds,
      unsigned port, unsigned device, unsigned idx, unsigned id)
{
   rwebinput_input_t *rwebinput  = (rwebinput_input_t*)data;

   switch (device)
   {
      case RETRO_DEVICE_JOYPAD:
         if (id == RETRO_DEVICE_ID_JOYPAD_MASK)
         {
            unsigned i;
            int16_t ret = 0;
            for (i = 0; i < RARCH_FIRST_CUSTOM_BIND; i++)
            {
               if (rwebinput_is_pressed(
                        rwebinput, joypad_info, port, binds[port], i))
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
               if (rwebinput_is_pressed(rwebinput, joypad_info, binds[port],
                     port, id))
                  return true;
         }
         break;
      case RETRO_DEVICE_ANALOG:
         {
            int16_t ret = rwebinput_analog_pressed(
                  rwebinput, joypad_info, binds[port],
                  idx, id);
            if (!ret && binds[port])
               ret = input_joypad_analog(rwebinput->joypad, joypad_info, port,
                     idx, id, binds[port]);
            return ret;
         }
      case RETRO_DEVICE_KEYBOARD:
         return rwebinput_key_pressed(rwebinput, id);
      case RETRO_DEVICE_MOUSE:
         return rwebinput_mouse_state(&rwebinput->mouse, id, false);
      case RARCH_DEVICE_MOUSE_SCREEN:
         return rwebinput_mouse_state(&rwebinput->mouse, id, true);
      case RETRO_DEVICE_POINTER:
         return rwebinput_pointer_device_state(&rwebinput->mouse, id, false);
      case RARCH_DEVICE_POINTER_SCREEN:
         return rwebinput_pointer_device_state(&rwebinput->mouse, id, true);
   }

   return 0;
}