#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_8__ {scalar_t__ keyboard_hid_handle; int* keyboard_state; int* prev_keys; scalar_t__ mouse_hid_handle; int mouse_button_left; int mouse_button_right; int mouse_button_middle; int mouse_x_delta; int mouse_y_delta; scalar_t__ mouse_x; scalar_t__ mouse_y; TYPE_1__* joypad; } ;
typedef  TYPE_2__ psp_input_t ;
struct TYPE_10__ {int* modifiers; int* keycodes; } ;
struct TYPE_9__ {int buttons; scalar_t__ rel_y; scalar_t__ rel_x; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* poll ) () ;} ;
typedef  TYPE_3__ SceHidMouseReport ;
typedef  TYPE_4__ SceHidKeyboardReport ;

/* Variables and functions */
 scalar_t__ MOUSE_MAX_X ; 
 scalar_t__ MOUSE_MAX_Y ; 
 int /*<<< orphan*/  RETROKMOD_ALT ; 
 int /*<<< orphan*/  RETROKMOD_CAPSLOCK ; 
 int /*<<< orphan*/  RETROKMOD_CTRL ; 
 int /*<<< orphan*/  RETROKMOD_META ; 
 int /*<<< orphan*/  RETROKMOD_NUMLOCK ; 
 int /*<<< orphan*/  RETROKMOD_SCROLLOCK ; 
 int /*<<< orphan*/  RETROKMOD_SHIFT ; 
 int /*<<< orphan*/  RETRO_DEVICE_KEYBOARD ; 
 int SCE_HID_MAX_REPORT ; 
 unsigned int VITA_NUM_MODIFIERS ; 
 int /*<<< orphan*/  input_keyboard_event (int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int input_keymaps_translate_keysym_to_rk (int) ; 
 int** modifier_lut ; 
 int sceHidKeyboardRead (scalar_t__,TYPE_4__**,int) ; 
 int sceHidMouseRead (scalar_t__,TYPE_3__**,int) ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static void psp_input_poll(void *data)
{
   psp_input_t *psp = (psp_input_t*)data;

   if (psp && psp->joypad)
      psp->joypad->poll();

#ifdef VITA
   unsigned int i = 0;
   int key_sym = 0;
   unsigned key_code = 0;
   uint8_t mod_code = 0;
   uint16_t mod = 0;
   uint8_t modifiers[2] = { 0, 0 };
   bool key_held = false;
   int numReports = 0;
   int mouse_velocity_x = 0;
   int mouse_velocity_y = 0;
   SceHidKeyboardReport k_reports[SCE_HID_MAX_REPORT];
   SceHidMouseReport m_reports[SCE_HID_MAX_REPORT];

   if (psp->keyboard_hid_handle > 0)
   {
      numReports = sceHidKeyboardRead(psp->keyboard_hid_handle, (SceHidKeyboardReport**)&k_reports, SCE_HID_MAX_REPORT);

      if (numReports < 0) {
         psp->keyboard_hid_handle = 0;
      }
      else if (numReports) {
         modifiers[0] = k_reports[numReports - 1].modifiers[0];
         modifiers[1] = k_reports[numReports - 1].modifiers[1];
         mod = 0;
         if (modifiers[0] & 0x11)
            mod |= RETROKMOD_CTRL;
         if (modifiers[0] & 0x22)
            mod |= RETROKMOD_SHIFT;
         if (modifiers[0] & 0x44)
            mod |= RETROKMOD_ALT;
         if (modifiers[0] & 0x88)
            mod |= RETROKMOD_META;
         if (modifiers[1] & 0x01)
            mod |= RETROKMOD_NUMLOCK;
         if (modifiers[1] & 0x02)
            mod |= RETROKMOD_CAPSLOCK;
         if (modifiers[1] & 0x04)
            mod |= RETROKMOD_SCROLLOCK;

         for (i = 0; i < VITA_NUM_MODIFIERS; i++)
         {
            key_sym = (int) modifier_lut[i][0];
            mod_code = modifier_lut[i][1];
            key_code = input_keymaps_translate_keysym_to_rk(key_sym);
            if (i < 8)
            {
               key_held = (modifiers[0] & mod_code);
            }
            else
            {
               key_held = (modifiers[1] & mod_code);
            }

            if (key_held && !(psp->keyboard_state[key_sym]))
            {
               psp->keyboard_state[key_sym] = true;
               input_keyboard_event(true, key_code, 0, mod, RETRO_DEVICE_KEYBOARD);
            }
            else if (!key_held && (psp->keyboard_state[key_sym]))
            {
               psp->keyboard_state[key_sym] = false;
               input_keyboard_event(false, key_code, 0, mod, RETRO_DEVICE_KEYBOARD);
            }
         }

         for (i = 0; i < 6; i++)
         {
            key_sym = k_reports[numReports - 1].keycodes[i];

            if (key_sym != psp->prev_keys[i])
            {
               if (psp->prev_keys[i])
               {
                  psp->keyboard_state[psp->prev_keys[i]] = false;
                  key_code = input_keymaps_translate_keysym_to_rk(psp->prev_keys[i]);
                  input_keyboard_event(false, key_code, 0, mod, RETRO_DEVICE_KEYBOARD);
               }
               if (key_sym)
               {
                  psp->keyboard_state[key_sym] = true;
                  key_code = input_keymaps_translate_keysym_to_rk(key_sym);
                  input_keyboard_event(true, key_code, 0, mod, RETRO_DEVICE_KEYBOARD);
               }
               psp->prev_keys[i] = key_sym;
            }
         }
      }
   }

   if (psp->mouse_hid_handle > 0)
   {
      numReports = sceHidMouseRead(psp->mouse_hid_handle, (SceHidMouseReport**)&m_reports, SCE_HID_MAX_REPORT);
      if (numReports > 0)
      {
         for (i = 0; i <= numReports - 1; i++)
         {
            uint8_t buttons = m_reports[i].buttons;

            if (buttons & 0x1)
            {
               psp->mouse_button_left = true;
            }
            else
            {
               psp->mouse_button_left = false;
            }

            if (buttons & 0x2)
            {
               psp->mouse_button_right = true;
            }
            else
            {
               psp->mouse_button_right = false;
            }

            if (buttons & 0x4)
            {
               psp->mouse_button_middle = true;
            }
            else
            {
               psp->mouse_button_middle = false;
            }

            mouse_velocity_x += m_reports[i].rel_x;
            mouse_velocity_y += m_reports[i].rel_y;
         }
      }
   }
   psp->mouse_x_delta = mouse_velocity_x;
   psp->mouse_y_delta = mouse_velocity_y;
   psp->mouse_x += mouse_velocity_x;
   psp->mouse_y += mouse_velocity_y;
   if (psp->mouse_x < 0)
   {
      psp->mouse_x = 0;
   }
   else if (psp->mouse_x > MOUSE_MAX_X)
   {
      psp->mouse_x = MOUSE_MAX_X;
   }

   if (psp->mouse_y < 0)
   {
      psp->mouse_y = 0;
   }
   else if (psp->mouse_y > MOUSE_MAX_Y)
   {
      psp->mouse_y = MOUSE_MAX_Y;
   }
#endif
}