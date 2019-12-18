#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct retro_keybind {unsigned int key; int /*<<< orphan*/  mbutton; int /*<<< orphan*/  joyaxis; int /*<<< orphan*/  joykey; int /*<<< orphan*/  valid; } ;
struct dinput_input {int* state; int mouse_rel_x; int mouse_rel_y; TYPE_3__* joypad; } ;
struct TYPE_8__ {float axis_threshold; int /*<<< orphan*/  joy_idx; TYPE_1__* auto_binds; } ;
typedef  TYPE_2__ rarch_joypad_info_t ;
typedef  int int16_t ;
typedef  enum retro_key { ____Placeholder_retro_key } retro_key ;
struct TYPE_10__ {int /*<<< orphan*/  keyboard_mapping_blocked; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* axis ) (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ;int /*<<< orphan*/  (* button ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  joyaxis; int /*<<< orphan*/  joykey; } ;

/* Variables and functions */
 int /*<<< orphan*/  AXIS_NONE ; 
 int /*<<< orphan*/  NO_BTN ; 
 unsigned int RARCH_BIND_LIST_END ; 
#define  RARCH_DEVICE_MOUSE_SCREEN 152 
#define  RARCH_DEVICE_POINTER_SCREEN 151 
 unsigned int RARCH_FIRST_CUSTOM_BIND ; 
 unsigned int RARCH_GAME_FOCUS_TOGGLE ; 
 unsigned int RARCH_LIGHTGUN_AUX_A ; 
 unsigned int RARCH_LIGHTGUN_AUX_B ; 
 unsigned int RARCH_LIGHTGUN_AUX_C ; 
 unsigned int RARCH_LIGHTGUN_DPAD_DOWN ; 
 unsigned int RARCH_LIGHTGUN_DPAD_LEFT ; 
 unsigned int RARCH_LIGHTGUN_DPAD_RIGHT ; 
 unsigned int RARCH_LIGHTGUN_DPAD_UP ; 
 unsigned int RARCH_LIGHTGUN_RELOAD ; 
 unsigned int RARCH_LIGHTGUN_SELECT ; 
 unsigned int RARCH_LIGHTGUN_START ; 
 unsigned int RARCH_LIGHTGUN_TRIGGER ; 
 unsigned int RETROK_LAST ; 
#define  RETRO_DEVICE_ANALOG 150 
 unsigned int RETRO_DEVICE_ID_JOYPAD_MASK ; 
#define  RETRO_DEVICE_ID_LIGHTGUN_AUX_A 149 
#define  RETRO_DEVICE_ID_LIGHTGUN_AUX_B 148 
#define  RETRO_DEVICE_ID_LIGHTGUN_AUX_C 147 
#define  RETRO_DEVICE_ID_LIGHTGUN_DPAD_DOWN 146 
#define  RETRO_DEVICE_ID_LIGHTGUN_DPAD_LEFT 145 
#define  RETRO_DEVICE_ID_LIGHTGUN_DPAD_RIGHT 144 
#define  RETRO_DEVICE_ID_LIGHTGUN_DPAD_UP 143 
#define  RETRO_DEVICE_ID_LIGHTGUN_IS_OFFSCREEN 142 
#define  RETRO_DEVICE_ID_LIGHTGUN_PAUSE 141 
#define  RETRO_DEVICE_ID_LIGHTGUN_RELOAD 140 
#define  RETRO_DEVICE_ID_LIGHTGUN_SCREEN_X 139 
#define  RETRO_DEVICE_ID_LIGHTGUN_SCREEN_Y 138 
#define  RETRO_DEVICE_ID_LIGHTGUN_SELECT 137 
#define  RETRO_DEVICE_ID_LIGHTGUN_START 136 
#define  RETRO_DEVICE_ID_LIGHTGUN_TRIGGER 135 
#define  RETRO_DEVICE_ID_LIGHTGUN_X 134 
#define  RETRO_DEVICE_ID_LIGHTGUN_Y 133 
#define  RETRO_DEVICE_JOYPAD 132 
#define  RETRO_DEVICE_KEYBOARD 131 
#define  RETRO_DEVICE_LIGHTGUN 130 
#define  RETRO_DEVICE_MOUSE 129 
#define  RETRO_DEVICE_POINTER 128 
 scalar_t__ abs (int /*<<< orphan*/ ) ; 
 int dinput_lightgun_aiming_state (struct dinput_input*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  dinput_mouse_button_pressed (struct dinput_input*,unsigned int,int /*<<< orphan*/ ) ; 
 int dinput_mouse_state (struct dinput_input*,unsigned int,unsigned int) ; 
 int dinput_mouse_state_screen (struct dinput_input*,unsigned int,unsigned int) ; 
 int dinput_pointer_state (struct dinput_input*,unsigned int,unsigned int,int) ; 
 int dinput_pressed_analog (struct dinput_input*,struct retro_keybind const*,unsigned int,unsigned int) ; 
 TYPE_5__ input_dinput ; 
 int input_joypad_analog (TYPE_3__*,TYPE_2__,unsigned int,unsigned int,unsigned int,struct retro_keybind const*) ; 
 size_t* rarch_keysym_lut ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 

__attribute__((used)) static int16_t dinput_input_state(void *data,
      rarch_joypad_info_t joypad_info,
      const struct retro_keybind **binds, unsigned port,
      unsigned device, unsigned idx, unsigned id)
{
   struct dinput_input *di    = (struct dinput_input*)data;

   switch (device)
   {
      case RETRO_DEVICE_JOYPAD:
         if (id == RETRO_DEVICE_ID_JOYPAD_MASK)
         {
            unsigned i;
            int16_t ret = 0;
            for (i = 0; i < RARCH_FIRST_CUSTOM_BIND; i++)
            {
               if (binds[port][i].key < RETROK_LAST)
               {
                  if (di->state[rarch_keysym_lut[(enum retro_key)binds[port][i].key]] & 0x80)
                     if ((i == RARCH_GAME_FOCUS_TOGGLE) || !input_dinput.keyboard_mapping_blocked)
                     {
                        ret |= (1 << i);
                        continue;
                     }
               }

               if (binds[port][i].valid)
               {
                  /* Auto-binds are per joypad, not per user. */
                     const uint64_t joykey  = (binds[port][i].joykey != NO_BTN)
                     ? binds[port][i].joykey : joypad_info.auto_binds[i].joykey;
                  const uint32_t joyaxis = (binds[port][i].joyaxis != AXIS_NONE)
                     ? binds[port][i].joyaxis : joypad_info.auto_binds[i].joyaxis;

                  if (dinput_mouse_button_pressed(
                           di, port, binds[port][i].mbutton))
                  {
                     ret |= (1 << i);
                     continue;
                  }

                  if ((uint16_t)joykey != NO_BTN
                        && di->joypad->button(
                           joypad_info.joy_idx, (uint16_t)joykey))
                  {
                     ret |= (1 << i);
                     continue;
                  }

                  if (((float)abs(di->joypad->axis(joypad_info.joy_idx, joyaxis)) / 0x8000) > joypad_info.axis_threshold)
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
            if (id < RARCH_BIND_LIST_END)
            {
               if (binds[port][id].key < RETROK_LAST)
               {
                  if (di->state[rarch_keysym_lut[(enum retro_key)binds[port][id].key]] & 0x80)
                     if ((id == RARCH_GAME_FOCUS_TOGGLE) || !input_dinput.keyboard_mapping_blocked)
                        return true;
               }
               if (binds[port][id].valid)
               {
                  /* Auto-binds are per joypad, not per user. */
                     const uint64_t joykey  = (binds[port][id].joykey != NO_BTN)
                     ? binds[port][id].joykey : joypad_info.auto_binds[id].joykey;
                  const uint32_t joyaxis = (binds[port][id].joyaxis != AXIS_NONE)
                     ? binds[port][id].joyaxis : joypad_info.auto_binds[id].joyaxis;

                  if (dinput_mouse_button_pressed(di, port, binds[port][id].mbutton))
                     return true;
                  if ((uint16_t)joykey != NO_BTN
                        && di->joypad->button(joypad_info.joy_idx, (uint16_t)joykey))
                     return true;
                  if (((float)abs(di->joypad->axis(joypad_info.joy_idx, joyaxis)) / 0x8000) > joypad_info.axis_threshold)
                     return true;
               }
            }
         }
         break;
      case RETRO_DEVICE_KEYBOARD:
         return (id < RETROK_LAST) && di->state[rarch_keysym_lut[(enum retro_key)id]] & 0x80;
      case RETRO_DEVICE_ANALOG:
         if (binds[port])
         {
            int16_t ret = dinput_pressed_analog(di, binds[port], idx, id);
            if (!ret)
               ret = input_joypad_analog(di->joypad, joypad_info,
                     port, idx, id, binds[port]);
            return ret;
         }
         return 0;

      case RETRO_DEVICE_MOUSE:
         return dinput_mouse_state(di, port, id);

      case RARCH_DEVICE_MOUSE_SCREEN:
         return dinput_mouse_state_screen(di, port, id);

      case RETRO_DEVICE_POINTER:
      case RARCH_DEVICE_POINTER_SCREEN:
         return dinput_pointer_state(di, idx, id,
               device == RARCH_DEVICE_POINTER_SCREEN);

      case RETRO_DEVICE_LIGHTGUN:
         switch (id)
         {
            /*aiming*/
            case RETRO_DEVICE_ID_LIGHTGUN_SCREEN_X:
            case RETRO_DEVICE_ID_LIGHTGUN_SCREEN_Y:
            case RETRO_DEVICE_ID_LIGHTGUN_IS_OFFSCREEN:
               return dinput_lightgun_aiming_state( di, idx, id);

               /*buttons*/
            case RETRO_DEVICE_ID_LIGHTGUN_TRIGGER:
            case RETRO_DEVICE_ID_LIGHTGUN_RELOAD:
            case RETRO_DEVICE_ID_LIGHTGUN_AUX_A:
            case RETRO_DEVICE_ID_LIGHTGUN_AUX_B:
            case RETRO_DEVICE_ID_LIGHTGUN_AUX_C:
            case RETRO_DEVICE_ID_LIGHTGUN_START:
            case RETRO_DEVICE_ID_LIGHTGUN_SELECT:
            case RETRO_DEVICE_ID_LIGHTGUN_DPAD_UP:
            case RETRO_DEVICE_ID_LIGHTGUN_DPAD_DOWN:
            case RETRO_DEVICE_ID_LIGHTGUN_DPAD_LEFT:
            case RETRO_DEVICE_ID_LIGHTGUN_DPAD_RIGHT:
            case RETRO_DEVICE_ID_LIGHTGUN_PAUSE:
               {
                  unsigned new_id = 0;
                  switch (id)
                  {
                     case RETRO_DEVICE_ID_LIGHTGUN_TRIGGER:
                        new_id = RARCH_LIGHTGUN_TRIGGER;
                        break;
                     case RETRO_DEVICE_ID_LIGHTGUN_RELOAD:
                        new_id = RARCH_LIGHTGUN_RELOAD;
                        break;
                     case RETRO_DEVICE_ID_LIGHTGUN_AUX_A:
                        new_id = RARCH_LIGHTGUN_AUX_A;
                        break;
                     case RETRO_DEVICE_ID_LIGHTGUN_AUX_B:
                        new_id = RARCH_LIGHTGUN_AUX_B;
                        break;
                     case RETRO_DEVICE_ID_LIGHTGUN_AUX_C:
                        new_id = RARCH_LIGHTGUN_AUX_C;
                        break;
                     case RETRO_DEVICE_ID_LIGHTGUN_START:
                        new_id = RARCH_LIGHTGUN_START;
                        break;
                     case RETRO_DEVICE_ID_LIGHTGUN_SELECT:
                        new_id = RARCH_LIGHTGUN_SELECT;
                        break;
                     case RETRO_DEVICE_ID_LIGHTGUN_DPAD_UP:
                        new_id = RARCH_LIGHTGUN_DPAD_UP;
                        break;
                     case RETRO_DEVICE_ID_LIGHTGUN_DPAD_DOWN:
                        new_id = RARCH_LIGHTGUN_DPAD_DOWN;
                        break;
                     case RETRO_DEVICE_ID_LIGHTGUN_DPAD_LEFT:
                        new_id = RARCH_LIGHTGUN_DPAD_LEFT;
                        break;
                     case RETRO_DEVICE_ID_LIGHTGUN_DPAD_RIGHT:
                        new_id = RARCH_LIGHTGUN_DPAD_RIGHT;
                        break;
                     case RETRO_DEVICE_ID_LIGHTGUN_PAUSE:
                        new_id = RARCH_LIGHTGUN_START;
                        break;
                  }
                  if (binds[port][new_id].key < RETROK_LAST)
                  {
                     if (di->state[rarch_keysym_lut[(enum retro_key)binds[port][new_id].key]] & 0x80)
                        if ((new_id == RARCH_GAME_FOCUS_TOGGLE) || !input_dinput.keyboard_mapping_blocked)
                           return true;
                  }
                  if (binds[port][new_id].valid)
                  {
                     /* Auto-binds are per joypad, not per user. */
                        const uint64_t joykey  = (binds[port][new_id].joykey != NO_BTN)
                        ? binds[port][new_id].joykey : joypad_info.auto_binds[new_id].joykey;
                     const uint32_t joyaxis = (binds[port][new_id].joyaxis != AXIS_NONE)
                        ? binds[port][new_id].joyaxis : joypad_info.auto_binds[new_id].joyaxis;

                     if (dinput_mouse_button_pressed(di, port, binds[port][new_id].mbutton))
                        return true;
                     if ((uint16_t)joykey != NO_BTN
                           && di->joypad->button(joypad_info.joy_idx, (uint16_t)joykey))
                        return true;
                     if (((float)abs(di->joypad->axis(joypad_info.joy_idx, joyaxis)) / 0x8000) > joypad_info.axis_threshold)
                        return true;
                  }
               }
               break;
               /*deprecated*/
            case RETRO_DEVICE_ID_LIGHTGUN_X:
               return di->mouse_rel_x;
            case RETRO_DEVICE_ID_LIGHTGUN_Y:
               return di->mouse_rel_y;
         }
			break;
   }

   return 0;
}