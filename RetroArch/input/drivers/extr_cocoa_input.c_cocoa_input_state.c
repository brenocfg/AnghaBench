#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct retro_keybind {size_t key; int /*<<< orphan*/  joyaxis; int /*<<< orphan*/  joykey; } ;
struct TYPE_11__ {float axis_threshold; int /*<<< orphan*/  joy_idx; TYPE_1__* auto_binds; } ;
typedef  TYPE_2__ rarch_joypad_info_t ;
typedef  int int16_t ;
typedef  enum retro_key { ____Placeholder_retro_key } retro_key ;
struct TYPE_12__ {TYPE_4__* joypad; TYPE_4__* sec_joypad; } ;
typedef  TYPE_3__ cocoa_input_data_t ;
struct TYPE_13__ {int /*<<< orphan*/  (* axis ) (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ;int /*<<< orphan*/  (* button ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_10__ {int /*<<< orphan*/  joyaxis; int /*<<< orphan*/  joykey; } ;

/* Variables and functions */
 int /*<<< orphan*/  AXIS_NONE ; 
 int /*<<< orphan*/  NO_BTN ; 
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
 scalar_t__ abs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * apple_key_state ; 
 int cocoa_mouse_state (TYPE_3__*,unsigned int) ; 
 int cocoa_mouse_state_screen (TYPE_3__*,unsigned int) ; 
 int cocoa_pointer_state (TYPE_3__*,unsigned int,unsigned int,unsigned int) ; 
 int input_joypad_analog (TYPE_4__*,TYPE_2__,unsigned int,unsigned int,unsigned int,struct retro_keybind const*) ; 
 size_t* rarch_keysym_lut ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 

__attribute__((used)) static int16_t cocoa_input_state(void *data,
      rarch_joypad_info_t joypad_info,
      const struct retro_keybind **binds, unsigned port,
      unsigned device, unsigned idx, unsigned id)
{
   cocoa_input_data_t *apple = (cocoa_input_data_t*)data;

   switch (device)
   {
      case RETRO_DEVICE_JOYPAD:
         if (id == RETRO_DEVICE_ID_JOYPAD_MASK)
         {
            unsigned i;
            int16_t ret = 0;
            for (i = 0; i < RARCH_FIRST_CUSTOM_BIND; i++)
            {
               /* Auto-binds are per joypad, not per user. */
               const uint64_t joykey  = (binds[port][i].joykey != NO_BTN)
                  ? binds[port][i].joykey : joypad_info.auto_binds[i].joykey;
               const uint32_t joyaxis = (binds[port][i].joyaxis != AXIS_NONE)
                  ? binds[port][i].joyaxis : joypad_info.auto_binds[i].joyaxis;

               if (apple_key_state[rarch_keysym_lut[binds[port][i].key]])
               {
                  ret |= (1 << i);
                  continue;
               }

               if ((uint16_t)joykey != NO_BTN && apple->joypad->button(joypad_info.joy_idx, (uint16_t)joykey))
               {
                  ret |= (1 << i);
                  continue;
               }
               if (((float)abs(apple->joypad->axis(joypad_info.joy_idx, joyaxis)) / 0x8000) > joypad_info.axis_threshold)
               {
                  ret |= (1 << i);
                  continue;
               }
#ifdef HAVE_MFI
               if ((uint16_t)joykey != NO_BTN && apple->sec_joypad->button(joypad_info.joy_idx, (uint16_t)joykey))
               {
                  ret |= (1 << i);
                  continue;
               }
               if (((float)abs(apple->sec_joypad->axis(joypad_info.joy_idx, joyaxis)) / 0x8000) > joypad_info.axis_threshold)
               {
                  ret |= (1 << i);
                  continue;
               }
#endif
            }
            return ret;
         }
         else
         {
            /* Auto-binds are per joypad, not per user. */
            const uint64_t joykey  = (binds[port][id].joykey != NO_BTN)
               ? binds[port][id].joykey : joypad_info.auto_binds[id].joykey;
            const uint32_t joyaxis = (binds[port][id].joyaxis != AXIS_NONE)
               ? binds[port][id].joyaxis : joypad_info.auto_binds[id].joyaxis;
            if (id < RARCH_BIND_LIST_END)
               if (apple_key_state[rarch_keysym_lut[binds[port][id].key]])
                  return true;
            if ((uint16_t)joykey != NO_BTN && apple->joypad->button(
                     joypad_info.joy_idx, (uint16_t)joykey))
               return true;
            if (((float)abs(apple->joypad->axis(joypad_info.joy_idx, joyaxis)) / 0x8000) > joypad_info.axis_threshold)
               return true;
#ifdef HAVE_MFI
            if ((uint16_t)joykey != NO_BTN && apple->sec_joypad->button(joypad_info.joy_idx, (uint16_t)joykey))
               return true;
            if (((float)abs(apple->sec_joypad->axis(joypad_info.joy_idx, joyaxis)) / 0x8000) > joypad_info.axis_threshold)
               return true;
#endif
         }
         break;
      case RETRO_DEVICE_ANALOG:
         {
            int16_t ret = 0;
#ifdef HAVE_MFI
            ret = input_joypad_analog(apple->sec_joypad, joypad_info, port,
                  idx, id, binds[port]);
#endif
            if (!ret && binds[port])
               ret = input_joypad_analog(apple->joypad, joypad_info, port,
                     idx, id, binds[port]);
            return ret;
         }
      case RETRO_DEVICE_KEYBOARD:
         return (id < RETROK_LAST) && apple_key_state[rarch_keysym_lut[(enum retro_key)id]];
      case RETRO_DEVICE_MOUSE:
         return cocoa_mouse_state(apple, id);
      case RARCH_DEVICE_MOUSE_SCREEN:
         return cocoa_mouse_state_screen(apple, id);
      case RETRO_DEVICE_POINTER:
      case RARCH_DEVICE_POINTER_SCREEN:
         return cocoa_pointer_state(apple, device, idx, id);
   }

   return 0;
}