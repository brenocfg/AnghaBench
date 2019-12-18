#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {unsigned int* input_libretro_device; unsigned int** input_keymapper_ids; unsigned int** input_remap_ids; } ;
struct TYPE_9__ {TYPE_1__ uints; } ;
typedef  TYPE_2__ settings_t ;
typedef  int int16_t ;
typedef  int /*<<< orphan*/  input_overlay_t ;
struct TYPE_10__ {int** analog_value; int /*<<< orphan*/ * buttons; int /*<<< orphan*/  keys; } ;
typedef  TYPE_3__ input_mapper_t ;
struct TYPE_11__ {int* analog_buttons; int* analogs; } ;
typedef  TYPE_4__ input_bits_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIT256_CLEAR_ALL (int /*<<< orphan*/ ) ; 
 unsigned int BIT256_GET (TYPE_4__,unsigned int) ; 
 int /*<<< orphan*/  BIT256_SET (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  INPUT_ACTION_AXIS_THRESHOLD ; 
 int /*<<< orphan*/  MAPPER_SET_KEY (TYPE_3__*,unsigned int) ; 
 unsigned int RARCH_CUSTOM_BIND_LIST_END ; 
 unsigned int RARCH_FIRST_CUSTOM_BIND ; 
 unsigned int RARCH_UNMAPPED ; 
 unsigned int RETROK_UNKNOWN ; 
#define  RETRO_DEVICE_ANALOG 130 
#define  RETRO_DEVICE_JOYPAD 129 
#define  RETRO_DEVICE_KEYBOARD 128 
 unsigned int RETRO_DEVICE_MASK ; 
 int abs (int) ; 
 int* input_driver_get_float (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_keyboard_event (int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const) ; 
 unsigned int input_overlay_key_pressed (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void input_mapper_poll(input_mapper_t *handle,
      void *ol_pointer,
      void *settings_data,
      void *input_data,
      unsigned max_users,
      bool poll_overlay)
{
   unsigned i, j;
#ifdef HAVE_OVERLAY
   input_overlay_t *overlay_pointer           = (input_overlay_t*)ol_pointer;
#endif
   settings_t *settings                       = (settings_t*)settings_data;
   input_bits_t *current_inputs               = (input_bits_t*)input_data;

   memset(handle->keys, 0, sizeof(handle->keys));

   for (i = 0; i < max_users; i++)
   {
      unsigned device  = settings->uints.input_libretro_device[i] 
         & RETRO_DEVICE_MASK;
      input_bits_t current_input = *current_inputs++;

      switch (device)
      {
         /* keyboard to gamepad remapping */
         case RETRO_DEVICE_KEYBOARD:
            for (j = 0; j < RARCH_CUSTOM_BIND_LIST_END; j++)
            {
               unsigned remap_button         =
                  settings->uints.input_keymapper_ids[i][j];
               bool remap_valid              = remap_button != RETROK_UNKNOWN;

               if (remap_valid)
               {
                  unsigned current_button_value = BIT256_GET(current_input, j);
#ifdef HAVE_OVERLAY
                  if (poll_overlay && i == 0)
                     current_button_value |= input_overlay_key_pressed(overlay_pointer, j);
#endif
                  if ((current_button_value == 1) && (j != remap_button))
                  {
                     MAPPER_SET_KEY (handle,
                           remap_button);
                     input_keyboard_event(true,
                           remap_button,
                           0, 0, RETRO_DEVICE_KEYBOARD);
                     continue;
                  }

                  /* Release keyboard event*/
                  input_keyboard_event(false,
                        remap_button,
                        0, 0, RETRO_DEVICE_KEYBOARD);
               }
            }
            break;

            /* gamepad remapping */
         case RETRO_DEVICE_JOYPAD:
         case RETRO_DEVICE_ANALOG:
            /* this loop iterates on all users and all buttons,
             * and checks if a pressed button is assigned to any
             * other button than the default one, then it sets
             * the bit on the mapper input bitmap, later on the
             * original input is cleared in input_state */
            BIT256_CLEAR_ALL(handle->buttons[i]);

            for (j = 0; j < 8; j++)
               handle->analog_value[i][j] = 0;

            for (j = 0; j < RARCH_FIRST_CUSTOM_BIND; j++)
            {
               bool remap_valid;
               unsigned remap_button         =
                  settings->uints.input_remap_ids[i][j];
               unsigned current_button_value = BIT256_GET(current_input, j);
#ifdef HAVE_OVERLAY
               if (poll_overlay && i == 0)
                  current_button_value |= input_overlay_key_pressed(overlay_pointer, j);
#endif
               remap_valid                   = (current_button_value == 1) &&
                  (j != remap_button) && (remap_button != RARCH_UNMAPPED);

               if (remap_valid)
               {
                  if (remap_button < RARCH_FIRST_CUSTOM_BIND)
                  {
                     BIT256_SET(handle->buttons[i], remap_button);
                  }
                  else if (remap_button >= RARCH_FIRST_CUSTOM_BIND)
                  {
                     int invert = 1;

                     if (remap_button % 2 != 0)
                        invert = -1;

                     handle->analog_value[i][
                        remap_button - RARCH_FIRST_CUSTOM_BIND] =
                           (current_input.analog_buttons[j] ? current_input.analog_buttons[j] : 32767) * invert;
                  }
               }
            }

            for (j = 0; j < 8; j++)
            {
               unsigned k                 = j + RARCH_FIRST_CUSTOM_BIND;
               int16_t current_axis_value = current_input.analogs[j];
               unsigned remap_axis        =
                  settings->uints.input_remap_ids[i][k];

               if (
                     (abs(current_axis_value) > 0 &&
                      (k != remap_axis)            &&
                      (remap_axis != RARCH_UNMAPPED)
                     ))
               {
                  if (remap_axis < RARCH_FIRST_CUSTOM_BIND &&
                        abs(current_axis_value) > *input_driver_get_float(INPUT_ACTION_AXIS_THRESHOLD) * 32767)
                  {
                     BIT256_SET(handle->buttons[i], remap_axis);
                  }
                  else
                  {
                     unsigned remap_axis_bind = remap_axis - RARCH_FIRST_CUSTOM_BIND;

                     if (remap_axis_bind < sizeof(handle->analog_value[i]))
                     {
                        int invert = 1;
                        if (  (k % 2 == 0 && remap_axis % 2 != 0) ||
                              (k % 2 != 0 && remap_axis % 2 == 0)
                           )
                           invert = -1;

                        handle->analog_value[i][
                           remap_axis_bind] =
                              current_axis_value * invert;
                     }
                  }
               }

            }
            break;
         default:
            break;
      }
   }
}