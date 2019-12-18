#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct retro_keybind {int /*<<< orphan*/  joykey; int /*<<< orphan*/  joyaxis; } ;
struct TYPE_12__ {float axis_threshold; int /*<<< orphan*/  joy_idx; TYPE_1__* auto_binds; } ;
typedef  TYPE_3__ rarch_joypad_info_t ;
typedef  int int16_t ;
struct TYPE_13__ {unsigned int pointer_count; TYPE_2__* pointer; TYPE_5__* joypad; } ;
typedef  TYPE_4__ android_input_t ;
struct TYPE_14__ {int /*<<< orphan*/  (* axis ) (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ;int /*<<< orphan*/  (* button ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_11__ {int x; int y; int full_x; int full_y; } ;
struct TYPE_10__ {int /*<<< orphan*/  joyaxis; int /*<<< orphan*/  joykey; } ;

/* Variables and functions */
 int /*<<< orphan*/  AKEYCODE_BACK ; 
 size_t ANDROID_KEYBOARD_PORT ; 
 int /*<<< orphan*/  AXIS_NONE ; 
 int /*<<< orphan*/  BIT_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NO_BTN ; 
#define  RARCH_DEVICE_ID_POINTER_BACK 139 
#define  RARCH_DEVICE_POINTER_SCREEN 138 
 unsigned int RARCH_FIRST_CUSTOM_BIND ; 
 size_t RARCH_MENU_TOGGLE ; 
 unsigned int RETROK_LAST ; 
#define  RETRO_DEVICE_ANALOG 137 
 unsigned int RETRO_DEVICE_ID_JOYPAD_MASK ; 
#define  RETRO_DEVICE_ID_POINTER_COUNT 136 
#define  RETRO_DEVICE_ID_POINTER_PRESSED 135 
#define  RETRO_DEVICE_ID_POINTER_X 134 
#define  RETRO_DEVICE_ID_POINTER_Y 133 
#define  RETRO_DEVICE_JOYPAD 132 
#define  RETRO_DEVICE_KEYBOARD 131 
#define  RETRO_DEVICE_LIGHTGUN 130 
#define  RETRO_DEVICE_MOUSE 129 
#define  RETRO_DEVICE_POINTER 128 
 scalar_t__ abs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * android_key_state ; 
 int android_keyboard_input_pressed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  android_keyboard_port_input_pressed (struct retro_keybind const*,unsigned int) ; 
 int android_lightgun_device_state (TYPE_4__*,unsigned int) ; 
 int android_mouse_state (TYPE_4__*,unsigned int) ; 
 struct retro_keybind** input_autoconf_binds ; 
 int input_joypad_analog (TYPE_5__*,TYPE_3__,unsigned int,unsigned int,unsigned int,struct retro_keybind const*) ; 
 int /*<<< orphan*/ * rarch_keysym_lut ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 

__attribute__((used)) static int16_t android_input_state(void *data,
      rarch_joypad_info_t joypad_info,
      const struct retro_keybind **binds, unsigned port, unsigned device,
      unsigned idx, unsigned id)
{
   android_input_t *android           = (android_input_t*)data;

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
               if ((uint16_t)joykey != NO_BTN && android->joypad->button(
                        joypad_info.joy_idx, (uint16_t)joykey))
               {
                  ret |= (1 << i);
                  continue;
               }
               if (((float)abs(android->joypad->axis(
                              joypad_info.joy_idx, joyaxis)) / 0x8000) > joypad_info.axis_threshold)
               {
                  ret |= (1 << i);
                  continue;
               }
               if (android_keyboard_port_input_pressed(binds[port], i))
                  ret |= (1 << i);
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
            if ((uint16_t)joykey != NO_BTN && android->joypad->button(
                     joypad_info.joy_idx, (uint16_t)joykey))
               return true;
            if (((float)abs(android->joypad->axis(
                           joypad_info.joy_idx, joyaxis)) / 0x8000) > joypad_info.axis_threshold)
               return true;
            if (android_keyboard_port_input_pressed(binds[port], id))
               return true;
         }
         break;
      case RETRO_DEVICE_ANALOG:
         if (binds[port])
            return input_joypad_analog(android->joypad, joypad_info,
                  port, idx, id, binds[port]);
         break;
      case RETRO_DEVICE_KEYBOARD:
         return (id < RETROK_LAST) && BIT_GET(android_key_state[ANDROID_KEYBOARD_PORT], rarch_keysym_lut[id]);
      case RETRO_DEVICE_MOUSE:
         return android_mouse_state(android, id);
      case RETRO_DEVICE_LIGHTGUN:
         return android_lightgun_device_state(android, id);
      case RETRO_DEVICE_POINTER:
         switch (id)
         {
            case RETRO_DEVICE_ID_POINTER_X:
               return android->pointer[idx].x;
            case RETRO_DEVICE_ID_POINTER_Y:
               return android->pointer[idx].y;
            case RETRO_DEVICE_ID_POINTER_PRESSED:
               return (idx < android->pointer_count) &&
                  (android->pointer[idx].x != -0x8000) &&
                  (android->pointer[idx].y != -0x8000);
            case RETRO_DEVICE_ID_POINTER_COUNT:
               return android->pointer_count;
            case RARCH_DEVICE_ID_POINTER_BACK:
            {
               const struct retro_keybind *keyptr = &input_autoconf_binds[0][RARCH_MENU_TOGGLE];
               if (keyptr->joykey == 0)
                  return android_keyboard_input_pressed(AKEYCODE_BACK);
            }
         }
         break;
      case RARCH_DEVICE_POINTER_SCREEN:
         switch (id)
         {
            case RETRO_DEVICE_ID_POINTER_X:
               return android->pointer[idx].full_x;
            case RETRO_DEVICE_ID_POINTER_Y:
               return android->pointer[idx].full_y;
            case RETRO_DEVICE_ID_POINTER_PRESSED:
               return (idx < android->pointer_count) &&
                  (android->pointer[idx].full_x != -0x8000) &&
                  (android->pointer[idx].full_y != -0x8000);
            case RETRO_DEVICE_ID_POINTER_COUNT:
               return android->pointer_count;
            case RARCH_DEVICE_ID_POINTER_BACK:
               {
                  const struct retro_keybind *keyptr = &input_autoconf_binds[0][RARCH_MENU_TOGGLE];
                  if (keyptr->joykey == 0)
                     return android_keyboard_input_pressed(AKEYCODE_BACK);
               }
         }
         break;
   }

   return 0;
}