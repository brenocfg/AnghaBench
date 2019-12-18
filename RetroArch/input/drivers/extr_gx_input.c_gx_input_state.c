#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct retro_keybind {int /*<<< orphan*/  joyaxis; int /*<<< orphan*/  joykey; } ;
struct TYPE_10__ {float axis_threshold; int /*<<< orphan*/  joy_idx; TYPE_1__* auto_binds; } ;
typedef  TYPE_2__ rarch_joypad_info_t ;
typedef  int int16_t ;
struct TYPE_11__ {TYPE_4__* joypad; } ;
typedef  TYPE_3__ gx_input_t ;
struct TYPE_12__ {int /*<<< orphan*/  (* axis ) (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ;int /*<<< orphan*/  (* button ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_9__ {int /*<<< orphan*/  joyaxis; int /*<<< orphan*/  joykey; } ;

/* Variables and functions */
 int /*<<< orphan*/  AXIS_NONE ; 
 unsigned int DEFAULT_MAX_PADS ; 
 int /*<<< orphan*/  NO_BTN ; 
 unsigned int RARCH_FIRST_CUSTOM_BIND ; 
#define  RETRO_DEVICE_ANALOG 131 
 unsigned int RETRO_DEVICE_ID_JOYPAD_MASK ; 
#define  RETRO_DEVICE_JOYPAD 130 
#define  RETRO_DEVICE_LIGHTGUN 129 
#define  RETRO_DEVICE_MOUSE 128 
 scalar_t__ abs (int /*<<< orphan*/ ) ; 
 int gx_lightgun_state (TYPE_3__*,unsigned int,int /*<<< orphan*/ ) ; 
 int gx_mouse_state (TYPE_3__*,unsigned int,int /*<<< orphan*/ ) ; 
 int input_joypad_analog (TYPE_4__*,TYPE_2__,unsigned int,unsigned int,unsigned int,struct retro_keybind const*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 

__attribute__((used)) static int16_t gx_input_state(void *data,
      rarch_joypad_info_t joypad_info,
      const struct retro_keybind **binds,
      unsigned port, unsigned device,
      unsigned idx, unsigned id)
{
   gx_input_t *gx             = (gx_input_t*)data;

   if (port >= DEFAULT_MAX_PADS || !gx)
      return 0;

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

               if ((uint16_t)joykey != NO_BTN && gx->joypad->button(joypad_info.joy_idx, (uint16_t)joykey))
               {
                  ret |= (1 << i);
                  continue;
               }
               if (((float)abs(gx->joypad->axis(joypad_info.joy_idx, joyaxis)) / 0x8000) > joypad_info.axis_threshold)
               {
                  ret |= (1 << i);
                  continue;
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

            if ((uint16_t)joykey != NO_BTN && gx->joypad->button(joypad_info.joy_idx, (uint16_t)joykey))
               return true;
            if (((float)abs(gx->joypad->axis(joypad_info.joy_idx, joyaxis)) / 0x8000) > joypad_info.axis_threshold)
               return true;
         }
         break;
      case RETRO_DEVICE_ANALOG:
         if (binds[port])
            return input_joypad_analog(gx->joypad,
                  joypad_info, port, idx, id, binds[port]);
         break;
#ifdef HW_RVL
      case RETRO_DEVICE_MOUSE:
         return gx_mouse_state(gx, id, joypad_info.joy_idx);

      case RETRO_DEVICE_LIGHTGUN:
         return gx_lightgun_state(gx, id, joypad_info.joy_idx);
#endif
   }

   return 0;
}