#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  input_remap_binds_enable; } ;
struct TYPE_15__ {unsigned int** input_remap_ids; int input_turbo_period; int input_turbo_duty_cycle; } ;
struct TYPE_17__ {TYPE_2__ bools; TYPE_1__ uints; } ;
typedef  TYPE_3__ settings_t ;
typedef  int int16_t ;
struct TYPE_18__ {int** analog; } ;
typedef  TYPE_4__ input_remote_state_t ;
struct TYPE_19__ {int* analog; int /*<<< orphan*/  buttons; } ;
typedef  TYPE_5__ input_overlay_state_t ;
struct TYPE_22__ {int* enable; int count; int /*<<< orphan*/ * frame_enable; } ;
struct TYPE_21__ {int /*<<< orphan*/  valid; } ;
struct TYPE_20__ {int /*<<< orphan*/  alive; TYPE_5__ overlay_state; } ;
struct TYPE_14__ {int** analog_value; int /*<<< orphan*/ * buttons; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT256_GET (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  MAPPER_GET_KEY (TYPE_10__*,unsigned int) ; 
 int /*<<< orphan*/  OVERLAY_GET_KEY (TYPE_5__*,unsigned int) ; 
 int /*<<< orphan*/  RARCH_FIRST_CUSTOM_BIND ; 
 unsigned int RARCH_FIRST_META_KEY ; 
 unsigned int RETROK_LAST ; 
#define  RETRO_DEVICE_ANALOG 133 
 unsigned int RETRO_DEVICE_ID_ANALOG_Y ; 
 unsigned int RETRO_DEVICE_ID_JOYPAD_RIGHT ; 
 unsigned int RETRO_DEVICE_ID_JOYPAD_UP ; 
 unsigned int RETRO_DEVICE_INDEX_ANALOG_RIGHT ; 
#define  RETRO_DEVICE_JOYPAD 132 
#define  RETRO_DEVICE_KEYBOARD 131 
#define  RETRO_DEVICE_LIGHTGUN 130 
#define  RETRO_DEVICE_MOUSE 129 
#define  RETRO_DEVICE_POINTER 128 
 TYPE_3__* configuration_settings ; 
 TYPE_10__* input_driver_mapper ; 
 int /*<<< orphan*/  input_driver_remote ; 
 TYPE_9__ input_driver_turbo_btns ; 
 int /*<<< orphan*/  input_remote_key_pressed (unsigned int,unsigned int) ; 
 TYPE_8__** libretro_input_binds ; 
 TYPE_7__* overlay_ptr ; 
 TYPE_4__ remote_st_ptr ; 

__attribute__((used)) static int16_t input_state_device(
      int16_t ret,
      unsigned port, unsigned device,
      unsigned idx, unsigned id,
      bool button_mask)
{
   int16_t res          = 0;
   settings_t *settings = configuration_settings;

#ifdef HAVE_NETWORKGAMEPAD
   bool remote_input    = false;
#endif

   switch (device)
   {
      case RETRO_DEVICE_JOYPAD:

#ifdef HAVE_NETWORKGAMEPAD
         if (input_driver_remote)
         {
            if (input_remote_key_pressed(id, port))
            {
               res |= 1;
               remote_input = true;
            }
         }
#endif

         if (id < RARCH_FIRST_META_KEY
#ifdef HAVE_NETWORKGAMEPAD
               /* Don't process binds if input is coming from Remote RetroPad */
               && remote_input == false
#endif
            )
         {
            bool bind_valid = libretro_input_binds[port]
               && libretro_input_binds[port][id].valid;

            if (settings->bools.input_remap_binds_enable &&
                  id != settings->uints.input_remap_ids[port][id])
               res = 0;
            else if (bind_valid)
            {
               if (button_mask)
               {
                  res = 0;
                  if (ret & (1 << id))
                     res |= (1 << id);
               }
               else
                  res = ret;

#ifdef HAVE_OVERLAY
               {
                  int16_t res_overlay  = 0;
                  if (overlay_ptr && port == 0 && overlay_ptr->alive)
                  {
                     if ((BIT256_GET(overlay_ptr->overlay_state.buttons, id)))
                        res_overlay |= 1;
                     if (overlay_ptr->alive)
                        res |= res_overlay;
                  }
               }
#endif
            }
         }

         if (settings->bools.input_remap_binds_enable && input_driver_mapper)
            if (BIT256_GET(input_driver_mapper->buttons[port], id))
               res = 1;

         /* Don't allow turbo for D-pad. */
         if ((id < RETRO_DEVICE_ID_JOYPAD_UP || id > RETRO_DEVICE_ID_JOYPAD_RIGHT))
         {
            /*
             * Apply turbo button if activated.
             *
             * If turbo button is held, all buttons pressed except
             * for D-pad will go into a turbo mode. Until the button is
             * released again, the input state will be modulated by a
             * periodic pulse defined by the configured duty cycle.
             */
            if (res && input_driver_turbo_btns.frame_enable[port])
               input_driver_turbo_btns.enable[port] |= (1 << id);
            else if (!res)
               input_driver_turbo_btns.enable[port] &= ~(1 << id);

            if (input_driver_turbo_btns.enable[port] & (1 << id))
            {
               /* if turbo button is enabled for this key ID */
               res = res && ((input_driver_turbo_btns.count
                        % settings->uints.input_turbo_period)
                     < settings->uints.input_turbo_duty_cycle);
            }
         }

         break;

      case RETRO_DEVICE_MOUSE:

         if (id < RARCH_FIRST_META_KEY)
         {
            bool bind_valid = libretro_input_binds[port]
               && libretro_input_binds[port][id].valid;

            if (bind_valid)
            {
               if (button_mask)
               {
                  res = 0;
                  if (ret & (1 << id))
                     res |= (1 << id);
               }
               else
                  res = ret;
            }
         }

         break;

      case RETRO_DEVICE_KEYBOARD:

         res = ret;

#ifdef HAVE_OVERLAY
         if (overlay_ptr && port == 0)
         {
            int16_t res_overlay  = 0;
            if (id < RETROK_LAST)
            {
               input_overlay_state_t *ol_state = &overlay_ptr->overlay_state;
               if (OVERLAY_GET_KEY(ol_state, id))
                  res_overlay |= 1;
            }

            if (overlay_ptr->alive)
               res |= res_overlay;
         }
#endif

         if (settings->bools.input_remap_binds_enable && input_driver_mapper)
            if (id < RETROK_LAST)
               if (MAPPER_GET_KEY(input_driver_mapper, id))
                  res |= 1;

         break;

      case RETRO_DEVICE_LIGHTGUN:

         if (id < RARCH_FIRST_META_KEY)
         {
            bool bind_valid = libretro_input_binds[port]
               && libretro_input_binds[port][id].valid;

            if (bind_valid)
            {
               if (button_mask)
               {
                  res = 0;
                  if (ret & (1 << id))
                     res |= (1 << id);
               }
               else
                  res = ret;
            }
         }

         break;

      case RETRO_DEVICE_ANALOG:

         {
#ifdef HAVE_OVERLAY
            int16_t res_overlay = 0;
            if (overlay_ptr && port == 0)
            {
               unsigned                   base = 0;
               input_overlay_state_t *ol_state = &overlay_ptr->overlay_state;

               if (idx == RETRO_DEVICE_INDEX_ANALOG_RIGHT)
                  base = 2;
               if (id == RETRO_DEVICE_ID_ANALOG_Y)
                  base += 1;
               if (ol_state && ol_state->analog[base])
                  res_overlay = ol_state->analog[base];
            }
#endif

#ifdef HAVE_NETWORKGAMEPAD
            if (input_driver_remote)
            {
               input_remote_state_t *input_state  = &remote_st_ptr;

               if (input_state)
               {
                  unsigned base = 0;
                  if (idx == RETRO_DEVICE_INDEX_ANALOG_RIGHT)
                     base = 2;
                  if (id == RETRO_DEVICE_ID_ANALOG_Y)
                     base += 1;
                  if (input_state->analog[base][port])
                  {
                     res = input_state->analog[base][port];
                     remote_input = true;
                  }
               }
            }
#endif

            if (id < RARCH_FIRST_META_KEY
#ifdef HAVE_NETWORKGAMEPAD
                  && remote_input == false
#endif
                )
            {
               bool bind_valid = libretro_input_binds[port]
                  && libretro_input_binds[port][id].valid;

               if (bind_valid)
               {
                  /* reset_state - used to reset input state of a button
                   * when the gamepad mapper is in action for that button*/
                  bool reset_state     = false;
                  if (settings->bools.input_remap_binds_enable)
                  {
                     if (idx < 2 && id < 2)
                     {
                        unsigned offset = RARCH_FIRST_CUSTOM_BIND +
                           (idx * 4) + (id * 2);

                        if (settings->uints.input_remap_ids
                              [port][offset]   != offset)
                           reset_state = true;
                        else if (settings->uints.input_remap_ids
                              [port][offset+1] != (offset+1))
                           reset_state = true;
                     }
                  }

                  if (!reset_state)
                  {
                     res = ret;

#ifdef HAVE_OVERLAY
                     if (overlay_ptr && overlay_ptr->alive && port == 0)
                        res |= res_overlay;
#endif
                  }
                  else
                     res = 0;
               }
            }

            if (settings->bools.input_remap_binds_enable && input_driver_mapper)
            {
               if (idx < 2 && id < 2)
               {
                  int         val = 0;
                  unsigned offset = 0 + (idx * 4) + (id * 2);
                  int        val1 = input_driver_mapper->analog_value[port][offset];
                  int        val2 = input_driver_mapper->analog_value[port][offset+1];

                  if (val1)
                     val          = val1;
                  else if (val2)
                     val          = val2;

                  if (val1 || val2)
                     res        |= val;
               }
            }
         }
         break;

      case RETRO_DEVICE_POINTER:

         if (id < RARCH_FIRST_META_KEY)
         {
            bool bind_valid = libretro_input_binds[port]
               && libretro_input_binds[port][id].valid;

            if (bind_valid)
            {
               if (button_mask)
               {
                  res = 0;
                  if (ret & (1 << id))
                     res |= (1 << id);
               }
               else
                  res = ret;
            }
         }

         break;
   }

   return res;
}