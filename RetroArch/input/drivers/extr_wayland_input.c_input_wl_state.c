#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct retro_keybind {size_t key; int /*<<< orphan*/  joyaxis; int /*<<< orphan*/  joykey; } ;
struct TYPE_15__ {float axis_threshold; int /*<<< orphan*/  joy_idx; TYPE_1__* auto_binds; } ;
typedef  TYPE_2__ rarch_joypad_info_t ;
typedef  int int16_t ;
struct TYPE_16__ {TYPE_11__* joypad; int /*<<< orphan*/  key_state; } ;
typedef  TYPE_3__ input_ctx_wayland_data_t ;
struct TYPE_14__ {int /*<<< orphan*/  joyaxis; int /*<<< orphan*/  joykey; } ;
struct TYPE_13__ {int /*<<< orphan*/  (* axis ) (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ;int /*<<< orphan*/  (* button ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AXIS_NONE ; 
 int /*<<< orphan*/  BIT_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int MAX_TOUCHES ; 
 int /*<<< orphan*/  NO_BTN ; 
 unsigned int RARCH_BIND_LIST_END ; 
#define  RARCH_DEVICE_MOUSE_SCREEN 135 
#define  RARCH_DEVICE_POINTER_SCREEN 134 
 unsigned int RARCH_FIRST_CUSTOM_BIND ; 
#define  RETRO_DEVICE_ANALOG 133 
 unsigned int RETRO_DEVICE_ID_JOYPAD_MASK ; 
#define  RETRO_DEVICE_JOYPAD 132 
#define  RETRO_DEVICE_KEYBOARD 131 
#define  RETRO_DEVICE_LIGHTGUN 130 
#define  RETRO_DEVICE_MOUSE 129 
#define  RETRO_DEVICE_POINTER 128 
 scalar_t__ abs (int /*<<< orphan*/ ) ; 
 int input_joypad_analog (TYPE_11__*,TYPE_2__,unsigned int,unsigned int,unsigned int,struct retro_keybind const*) ; 
 int input_wl_analog_pressed (TYPE_3__*,struct retro_keybind const*,unsigned int,unsigned int) ; 
 int input_wl_lightgun_state (TYPE_3__*,unsigned int) ; 
 int input_wl_mouse_state (TYPE_3__*,unsigned int,int) ; 
 int input_wl_pointer_state (TYPE_3__*,unsigned int,unsigned int,int) ; 
 int input_wl_state_kb (TYPE_3__*,struct retro_keybind const**,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 int input_wl_touch_state (TYPE_3__*,unsigned int,unsigned int,int) ; 
 int /*<<< orphan*/ * rarch_keysym_lut ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 

__attribute__((used)) static int16_t input_wl_state(void *data,
      rarch_joypad_info_t joypad_info,
      const struct retro_keybind **binds,
      unsigned port, unsigned device, unsigned idx, unsigned id)
{
   input_ctx_wayland_data_t *wl = (input_ctx_wayland_data_t*)data;

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
               if (BIT_GET(wl->key_state, rarch_keysym_lut[binds[port][i].key]) )
               {
                  ret |= (1 << i);
                  continue;
               }

               if (binds[port])
               {
                  if ((uint16_t)joykey != NO_BTN && wl->joypad->button(joypad_info.joy_idx, (uint16_t)joykey))
                  {
                     ret |= (1 << i);
                     continue;
                  }
                  if (((float)abs(wl->joypad->axis(joypad_info.joy_idx, joyaxis)) / 0x8000) > joypad_info.axis_threshold)
                  {
                     ret |= (1 << i);
                     continue;
                  }
               }
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
               if (BIT_GET(wl->key_state, rarch_keysym_lut[binds[port][id].key]))
                  return true;

            if (binds[port])
            {
               if ((uint16_t)joykey != NO_BTN && wl->joypad->button(joypad_info.joy_idx, (uint16_t)joykey))
                  return true;
               if (((float)abs(wl->joypad->axis(joypad_info.joy_idx, joyaxis)) / 0x8000) > joypad_info.axis_threshold)
                  return true;
            }
         }
         break;
      case RETRO_DEVICE_ANALOG:
         {
            int16_t ret = input_wl_analog_pressed(wl, binds[port], idx, id);
            if (!ret && binds[port])
               ret = input_joypad_analog(wl->joypad, joypad_info, port, idx, id, binds[port]);
            return ret;
         }
      case RETRO_DEVICE_KEYBOARD:
         return input_wl_state_kb(wl, binds, port, device, idx, id);
      case RETRO_DEVICE_MOUSE:
         return input_wl_mouse_state(wl, id, false);
      case RARCH_DEVICE_MOUSE_SCREEN:
         return input_wl_mouse_state(wl, id, true);

      case RETRO_DEVICE_POINTER:
         if (idx == 0)
            return input_wl_pointer_state(wl, idx, id,
                  device == RARCH_DEVICE_POINTER_SCREEN);
         break;
      case RARCH_DEVICE_POINTER_SCREEN:
         if (idx < MAX_TOUCHES)
            return input_wl_touch_state(wl, idx, id,
                  device == RARCH_DEVICE_POINTER_SCREEN);
         break;
      case RETRO_DEVICE_LIGHTGUN:
         return input_wl_lightgun_state(wl, id);
   }

   return 0;
}